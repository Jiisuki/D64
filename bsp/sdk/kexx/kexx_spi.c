/** @file
 *  @brief SPI driver implementation.
 */

#include <mcu.h>
#include <stdint.h>
#include "kexx_spi.h"

/* Initialises the SPI module. */
/*----------------------------------------------------------------------------*/
void SPI_init(const SPIModule_t* const mod)
{
    /* Pinout */
    if (SPI0 == mod->base)
    {
        if (kSPI_PS0 == mod->pinout)
        {
            SIM->PINSEL &= ~SIM_PINSEL_SPI0PS_MASK;
        }
        else
        {
            SIM->PINSEL |= SIM_PINSEL_SPI0PS_MASK;
        }
        SIM->SCGC |= SIM_SCGC_SPI0_MASK;
    }
    else if (SPI1 == mod->base)
    {
        if (kSPI_PS0 == mod->pinout)
        {
            SIM->PINSEL1 &= ~SIM_PINSEL1_SPI1PS_MASK;
        }
        else
        {
            SIM->PINSEL1 |= SIM_PINSEL1_SPI1PS_MASK;
        }
        SIM->SCGC |= SIM_SCGC_SPI1_MASK;
    }

    /* SPI config */
    mod->base->C1 = ((mod->masterSlave << SPI_C1_MSTR_SHIFT) |
                     (mod->clockPolarity << SPI_C1_CPOL_SHIFT) |
                     (mod->clockPhase << SPI_C1_CPHA_SHIFT) |
                     (mod->bitOrder << SPI_C1_LSBFE_SHIFT) |
                     SPI_C1_SSOE_MASK);

    mod->base->C2 = ((mod->faultMode << SPI_C2_MODFEN_SHIFT) |
                     (mod->bidirectionalMode << SPI_C2_BIDIROE_SHIFT) |
                     (mod->powerConservation << SPI_C2_SPISWAI_SHIFT) |
                     (mod->bidirectionalPinControl << SPI_C2_SPC0_SHIFT));

    /* Configure baudrate. */
    /* BaudRateDivisor = (SPPR + 1) * 2^(SPR + 1) */
    /* BaudRate        = BusClock / BaudRateDivisor */
    /* BaudRate        = (SystemClock/2) / ((SPPR+1)*2^(SPR+1)) */
    /* this is inefficient, but should find the closest combination: */

    uint32_t currentBaud = 0;
    uint32_t bestBaudDifference = 0xffffffff;

    /* memory of the best config so far */
    uint8_t bestPrescaler = 0;
    uint8_t bestDivider = 0;
    /* step through all possible prescaler values */
    for (uint8_t prescaler = 0; prescaler < 8; prescaler++)
    {
        /* step through all possible divider values */
        for (uint8_t divider = 0; divider < 9; divider++)
        {
            /* Calculate current buadrate. */
            currentBaud = (SystemCoreClock/2) / ((prescaler+1) * (2u << divider));

            /* Get the difference between current baud and the required baud. */
            uint32_t currentBaudDifference = (currentBaud < mod->baudrate) ?
                (mod->baudrate - currentBaud) :
                (currentBaud - mod->baudrate);

            /* If this config was better than the last, update best config values. */
            if (currentBaudDifference < bestBaudDifference)
            {
                bestPrescaler = prescaler;
                bestDivider = divider;
                bestBaudDifference = currentBaudDifference;
            }
        }
    }

    /* We should have the optimum config now for baudrate. */
    mod->base->BR = (((bestPrescaler << SPI_BR_SPPR_SHIFT) & SPI_BR_SPPR_MASK) | ((bestDivider << SPI_BR_SPR_SHIFT) & SPI_BR_SPR_MASK));

    /* Enable SPI. */
    mod->base->C1 |= SPI_C1_SPE_MASK;
}

/* Initialises the SPI module. */
/*----------------------------------------------------------------------------*/
void SPI_deinit(const SPIModule_t* const mod)
{
    // Disable SPI module. Hardfault?
    //mod->base->C1 &= ~SPI_C1_SPE_MASK;

    // Disable clock to the module.
    if (SPI0 == mod->base)
    {
        SIM->SCGC &= ~SIM_SCGC_SPI0_MASK;
    }
    else if (SPI1 == mod->base)
    {
        SIM->SCGC &= ~SIM_SCGC_SPI1_MASK;
    }
}

/* Enables or disables interrupts on a specific module. */
/*----------------------------------------------------------------------------*/
void SPI_setupInterrupts(const SPIModule_t* mod,
                          const SPISPIE_t spie,
                          const SPISPTIE_t sptie,
                          const SPISPMIE_t mie)
{
    if (kSPI_SPIE_ENABLE_INTERRUPT == spie)
    {
        mod->base->C1 |= SPI_C1_SPIE_MASK;
    }
    else
    {
        mod->base->C1 &= ~SPI_C1_SPIE_MASK;
    }

    if (kSPI_SPTIE_ENABLE_TRANSMIT_INTERRUPT == sptie)
    {
        mod->base->C1 |= SPI_C1_SPTIE_MASK;
    }
    else
    {
        mod->base->C1 &= ~SPI_C1_SPTIE_MASK;
    }

    if (kSPI_SPMIE_ENABLE_MATCH_INTERRUPT == mie)
    {
        mod->base->C2 |= SPI_C2_SPMIE_MASK;
    }
    else
    {
        mod->base->C2 &= ~SPI_C2_SPMIE_MASK;
    }
}

/* Sends data on the SPI bus. */
/*----------------------------------------------------------------------------*/
uint8_t SPI_transfer(const SPIModule_t* mod, uint8_t value)
{
    while (0 == (mod->base->S & SPI_S_SPTEF_MASK))
    {
        /* Wait until we can put data on buffer. */
    }

    mod->base->D = value;

    while (0 == (mod->base->S & SPI_S_SPRF_MASK))
    {
        /* Wait until data is available in buffer. */
    }

    return (mod->base->D & 0xFF);
}


