/*
 * iec.c
 *
 *  Created on: 26 Apr 2018
 *      Author: Jiisuki
 */

#include "iecIface.h"

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#ifndef WIN32
#include "fsl_gpio.h"
#endif

#include "d64Iface.h"
#include "fifoIface.h"
#include "delayIface.h"

#undef USE_IEC_ATN_MACRO

static uint8_t fifoBuffer[D64_FIELD_SIZE_NAME];

static struct
{
    IEC_USB_State_t USB;
    IEC_Disc_State_t disc;
    bool EOIf;
    FIFO_t fifo;
    uint8_t byte;
    bool fifoFull;
} iec;


static void IEC_setDAT(const IEC_Output_t value);
static void IEC_setCLK(const IEC_Output_t value);
#ifdef USE_IEC_ATN_MACRO
static void IEC_setATN(const IEC_Output_t value);
#endif

static IEC_Input_t IEC_readDAT(void);
static IEC_Input_t IEC_readCLK(void);
#ifdef USE_IEC_ATN_MACRO
static IEC_Input_t IEC_readATN(void);
#endif

void IEC_init(void)
{
    iec.EOIf = false;
    iec.USB = USB_STATE_IDLE;
    iec.byte = 0;
    iec.fifoFull = false;

    (void) FIFO_init(&iec.fifo, fifoBuffer, D64_FIELD_SIZE_NAME);
}

uint8_t IEC_comRX()
{
    /* Returns type, NULL, command or byte. */
    if (IEC_COM_State_Rx != iec.disc.communication)
    {
        return DATA_NULL;
    }

    /* We have identified this as reception, */
    /* ready to recieve data. */
    IEC_setDAT(IEC_Output_True);
    IEC_setCLK(IEC_Output_False);

    iec.EOIf = false;

    /* We are listener, wait for clock to go false. */
    while (IEC_Input_False != IEC_readCLK())
    {
        /* Wait.. */
    }

    /* C64 has indicated ready to send (RTS). */
    iec.fifoFull = false;

    IEC_setDAT(IEC_Output_False);

    /* Wait for C64 to accept, or do we get EOI after timeout? */
    while (IEC_Input_True != IEC_readCLK())
    {
        Delay_us(1);

        /* Request timed out, EOI. */
        iec.EOIf = true;
        IEC_setDAT(IEC_Output_True);

        Delay_us(IEC_DA_MIN);

        /* EOI Ack. */
        IEC_setDAT(IEC_Output_False);

        /* Wait for transmission start from C64. */
        while (IEC_Input_True != IEC_readCLK())
        {
            // Wait.
        }
    }

    /* Start transmission. */
    /* We want to recieve 8 bits. */
    uint8_t nBits = 0;
    while (nBits < 8)
    {
        /* Wait for data ready. */
        while (IEC_Input_False != IEC_readCLK())
        {
            // Wait ..
        }

        /* Data ready, grab bit to fifo. */
        const uint8_t byte = (uint8_t) IEC_readDAT();
        (void) FIFO_write(&iec.fifo, byte);

        nBits++;

        /* wait for next new bit */
        while (IEC_Input_True != IEC_readCLK())
        {
            // Wait..
        }
    }

    /* Acknowledge byte. */
    IEC_setDAT(IEC_Output_True);

    /* What do we do next? was it the last byte or so? */
    if (iec.EOIf)
    {
        iec.disc.communication = IEC_COM_State_Idle;
    }

    return (DATA_BYTE);
}

uint8_t IEC_TRANSMISSION_TX(uint8_t IEC_SEND_BYTE, uint8_t EOI){
    if (IEC_COM_State_Tx != iec.disc.communication)
    {
        return DATA_NULL;
    }

    /* kinda like the above, but reversed and some diff times */

    // IEC_SEND_BYTE is the data to send, should be loaded before this is called
    /* we are ready to transmit data */
    IEC_setDAT(IEC_Output_False);
    IEC_setCLK(IEC_Output_True);

    /* we are talker, wait for dat to go true */
    while (IEC_Input_True != IEC_readDAT())
    {

    }

    /* c64 has indicated available */

    /* start transmission */
    IEC_setCLK(IEC_Output_False);

    /* indicate ready to send */

    while (IEC_Input_False != IEC_readDAT())
    {

    }

    /* ready for data */

    if (EOI)
    {
        /**************************************************************************/
        /* Go EOI here, we need to wait for a while before taking clock line true */
        /**************************************************************************/
        Delay_us(IEC_YE_TYP);

        IEC_setCLK(IEC_Output_True);

        while (IEC_Input_True != IEC_readDAT())
        {
            /* wait for EOI ack */
            Delay_us(1000);
        }

        iec.disc.communication = IEC_COM_State_Idle;

        Delay_us(IEC_EI_MIN_TALK);
    }

    /* start transmission */
    IEC_setCLK(IEC_Output_True);

    Delay_us(60);

    /* we want to send 8 bits */
    uint8_t nBits = 0;
    while (nBits < 8)
    {
        IEC_setCLK(IEC_Output_False);
        IEC_setDAT(IEC_SEND_BYTE & 0x01); // NOTE: Negate if strange results..
        IEC_SEND_BYTE = IEC_SEND_BYTE >> 1u;

        Delay_us(IEC_S_TYP);

        IEC_setCLK(IEC_Output_True);

        Delay_us(IEC_V_MIN_TALK);

        nBits++;
    }

    /* release DAT */
    IEC_setDAT(IEC_Output_False);

    /* check for ACK */
    while (IEC_Input_True != IEC_readDAT())
    {
        Delay_us(IEC_PR_MIN_TALK);

        if (IEC_Input_True == IEC_readDAT())
        {
            /* Abort. */
            iec.disc.communication = IEC_COM_State_Idle;
            return (0xff);
        }
    }

    Delay_us(IEC_BB_MIN);

    return (0x00);
}

static void IEC_setDAT(const IEC_Output_t value)
{

}

static void IEC_setCLK(const IEC_Output_t value)
{

}

#ifdef USE_IEC_ATN_MACRO
static void IEC_setATN(const IEC_Output_t value)
{

}
#endif

static IEC_Input_t IEC_readDAT(void)
{
#ifndef WIN32
    const IEC_Input_t result = (GPIO_PinRead(kGPIO_PORTA, 0)) ? IEC_Input_False : IEC_Input_True;
#else
    const IEC_Input_t result = IEC_Input_False;
#endif
    return (result);
}

static IEC_Input_t IEC_readCLK(void)
{
#ifndef WIN32
    const IEC_Input_t result = (GPIO_PinRead(kGPIO_PORTA, 0)) ? IEC_Input_False : IEC_Input_True;
#else
    const IEC_Input_t result = IEC_Input_False;
#endif
    return (result);
}

#ifdef USE_IEC_ATN_MACRO
static IEC_Input_t IEC_readATN(void)
{
#ifndef WIN32
    const IEC_Input_t result = (GPIO_PinRead(kGPIO_PORTA, 0)) ? IEC_Input_False : IEC_Input_True;
#else
    const IEC_Input_t result = IEC_Input_False;
#endif
    return (result);
}
#endif
