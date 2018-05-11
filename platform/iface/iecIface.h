/*
 * iec.h
 *
 *  Created on: 26 Apr 2018
 *      Author: Jiisuki
 */

#pragma once

#include <stdint.h>

/* states of the disk drive */
typedef enum
{
    STATE_DEVICE_CLOSED,
    STATE_DEVICE_LISTENER,
    STATE_DEVICE_TALKER,
} IEC_Device_State_t;

/* states of the comm channes */
typedef enum
{
    STATE_CHANNEL_CLOSED,
    STATE_CHANNEL_OPEN,
    STATE_CHANNEL_OPEN_DAT,
} IEC_COM_Channel_State_t;

/* attention states */
#define ATTENTION_NULL   1
#define ATTENTION_ACTIVE 0

/* comm states */
typedef enum
{
    IEC_COM_State_Idle,
    IEC_COM_State_Rx,
    IEC_COM_State_Tx,
} IEC_COM_State_t;

#define DATA_NULL 0
#define DATA_BYTE 1

typedef struct
{
    uint8_t attention;
    uint8_t disk;
    IEC_COM_State_t communication;
    uint8_t channel;
    uint8_t loadingType;
    uint8_t transmissionStatus;
    uint8_t byteCounter;
    uint16_t timer;
} IEC_Disc_State_t;

typedef struct
{
    uint8_t State;
    uint8_t Track;
    uint8_t Sector;
    uint16_t Timeout;
    uint8_t ByteCounter;
} D64_Disc_State_t;

/* c64 iec bus signals */
typedef enum
{
    IEC_Output_False = 0,
    IEC_Output_True = 1,
} IEC_Output_t;

typedef enum
{
    IEC_Input_False = 1,
    IEC_Input_True = 0,
} IEC_Input_t;

/* the same times as above but in commodore lang */
/* all times in us otherwise stated, excluded zero times or missing */
#define IEC_AT_MAX 1000 /* ATN response (required) */
#define IEC_H_MIN     0 /* listener holdoff */
#define IEC_NE_TYP   40 /* non-eoi response to rfd */
#define IEC_NE_MAX  200
#define IEC_S_MIN    20 /* bit setup talker */
#define IEC_S_TYP    70
#define IEC_V_MIN    20 /* data valid */
#define IEC_V_MIN_TALK 60
#define IEC_V_TYP    20
#define IEC_F_TYP    20 /* frame handshake */
#define IEC_F_MAX  1000
#define IEC_R_MIN    20 /* frame to release of ATN */
#define IEC_BB_MIN  100 /* between bytes time */
#define IEC_YE_MIN  200 /* eoi response time */
#define IEC_YE_TYP  250
#define IEC_EI_MIN   60 /* eoi response hold time */
#define IEC_EI_MIN_TALK  80 /* eoi response hold time */
#define IEC_RY_TYP   30 /* talker response limit */
#define IEC_RY_MAX   60
#define IEC_PR_MIN   20 /* byte-ack */
#define IEC_PR_MIN_TALK 60
#define IEC_PR_TYP   30
#define IEC_TK_MIN   20 /* talk-attention release */
#define IEC_TK_TYP   30
#define IEC_TK_MAX  100
#define IEC_DA_MIN   80 /* talk-attention ack. hold */
#define IEC_FR_MIN   60 /* eoi ack. */

#define IEC_TIMER_RESET 0

/* c64 commands that can be read */
/* instructions to the disk drive */
#define DEVICE_ID     0x08 // primary disk drive
typedef enum
{
    IEC_Command_Listen   = 0x20,
    IEC_Command_Unlisten = 0x3f,
    IEC_Command_Talk     = 0x40,
    IEC_Command_Untalk   = 0x5f,
    IEC_Command_OpenDat  = 0x60,
    IEC_Command_Close    = 0xe0,
    IEC_Command_Open     = 0xf0,
} IEC_Command_t;

/* usb read write states */
typedef enum
{
    USB_STATE_WRITE            = 0xbd,
    USB_STATE_GET_TRACK        = 0x10,
    USB_STATE_GET_SECTOR       = 0x20,
    USB_STATE_IDLE             = 0x00,
    USB_STATE_READ             = 0xfd,
    USB_STATE_PROGRAMMING      = 0xf0,
    USB_STATE_FORMAT           = 0xed,
    USB_STATE_GET_FLASH_STATUS = 0x68,
    USB_STATE_GET_DISK_INFO    = 0x48,
    USB_STATE_BURN_BYTE        = 0xbb,
    USB_STATE_READ_BYTE        = 0xfb,
    USB_STATE_READ_RESET       = 0xfa,
} IEC_USB_State_t;

void IEC_init(void);

uint8_t IEC_TRANSMISSION_RX(void); /* recieve byte and return OK */
uint8_t IEC_TRANSMISSION_TX(uint8_t IEC_SEND_BYTE, uint8_t EOI); /* transmit byte */

