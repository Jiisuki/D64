/** @file
 *  @defgroup SPI SPI Driver
 *  @ingroup KEXX
 *  @brief SPI driver implementation.
 */

#pragma once

/** @addtogroup SPI
 *  @{ */

#include <mcu.h>

/** @brief Describes the routing of the SPI module to MCU pins. */
typedef enum
{
    kSPI_PS0 = 0U, /**< SPI_0 SCK/MOSI/MISO/CS = PTB<2:5>, SPI_1 SCK/MOSI/MISO/CS = PTD<0:3> */
    kSPI_PS1 = 1U, /**< SPI_0 SCK/MOSI/MISO/CS = PTE<0:3>, SPI_1 SCK/MOSI/MISO/CS = PTG<4:7> */
} SPIPinout_t;

/** @name SPI_C1
 *  Settings for SPI_C1 field.
 *  @{ */

/** @brief Interrupt enable general. */
typedef enum
{
    kSPI_SPIE_ENABLE_INTERRUPT = 1U,  /**< Enables interrupts. */
    kSPI_SPIE_DISABLE_INTERRUPT = 0U, /**< Disables interrupts. */
} SPISPIE_t;

/** @brief Transmit interrupt enable. */
typedef enum
{
    kSPI_SPTIE_ENABLE_TRANSMIT_INTERRUPT = 1U,  /**< Enables transmit interrupt. */
    kSPI_SPTIE_DISABLE_TRANSMIT_INTERRUPT = 0U, /**< Disables transmit interrupt. */
} SPISPTIE_t;

/** @brief Master/slave mode. */
typedef enum
{
    kSPI_MSTR_MASTER = 1U, /**< SPI operates as master. */
    kSPI_MSTR_SLAVE = 0U,  /**< SPI operates as slave. */
} SPIMSTR_t;

/** @brief Clock polarity. */
typedef enum
{
    kSPI_CPOL_ACTIVE_HIGH_CLOCK = 0U, /**< Clock active high. */
    kSPI_CPOL_ACTIVE_LOW_CLOCK = 1U,  /**< Clock active low. */
} SPICPOL_t;

/** @brief Clock phase. */
typedef enum
{
    kSPI_CPHA_FIRST_EDGE_AT_MIDDLE_OF_TRANSFER = 0U, /**< Clocks first edge at middle of transfer. */
    kSPI_CPHA_FIRST_EDGE_AT_START_OF_TRANSFER = 1U,  /**< Clocks first edge at start of transfer. */
} SPICPHA_t;

/** @brief Endian setting. */
typedef enum
{
    kSPI_LSBFE_START_WITH_MSB = 0U, /**< Transmission starts with most significant bit. */
    kSPI_LSBFE_START_WITH_LSB = 1U, /**< Transmission starts with least significant bit. */
} SPILSBFE_t;
/** @} */

/** @name SPI_C2
 *  Settings for SPI_C2 field.
 *  @{ */

/** @brief Match interrupt setting. */
typedef enum
{
    kSPI_SPMIE_DISABLE_MATCH_INTERRUPT = 0U, /**< Disable interrupt on data match. */
    kSPI_SPMIE_ENABLE_MATCH_INTERRUPT = 1U,  /**< Enable interrupt on data match. */
} SPISPMIE_t;

/** @brief Fault mode setting.
 *  If fault mode is disabled, ~SS-pin is a GPIO in master mode.
 *  If fault mode is enabled, ~SS-pin is fault mode input or slave select output in master mode, depending on other settings. */
typedef enum
{
    kSPI_MODFEN_FAULT_MODE_DISABLED = 0U, /**< Fault mode disabled, ~SS-pin is a GPIO if master mode is set. */
    kSPI_MODFEN_FAULT_MODE_ENABLED = 1U,  /**< Fault mode enabled, ~SS-pin is fault input or SS output in master mode, depending on other settings. */
} SPIMODFEN_t;

/** @brief Bidirectional mode setting. */
typedef enum
{
    kSPI_BIDIROE_MOMI_SISO_MODE = 1U, /**< Single wire bidirectional setting, MOMI/SISO mode. */
    kSPI_BIDIROE_MOSI_MISO_MODE = 0U, /**< Normal MOSI/MISO mode. */
} SPIBIDIROE_t;

/** @brief Settings for wait modes. */
typedef enum
{
    kSPI_SPISWAI_NO_WAIT = 0U, /**< SPI clocks operational in wait mode. */
    kSPI_SPISWAI_WAIT = 1U,    /**< SPI clocks stop when in wait mode. */
} SPISPISWAI_t;

/** @brief Bidirectional mode setting, part B. */
typedef enum
{
    kSPI_SPC0_BIDIRECTIONAL_MOSI_MISO_MODE = 0U, /**< Normal MOSI/MISO mode. */
    kSPI_SPC0_BIDIRECTIONAL_SINGLE_MODE = 1U,    /**< Single-wire mode. */
} SPISPC0_t;
/** @} */

/** @brief Description of the SPI module. */
typedef struct
{
    SPI_Type* base;                    /**< Base address to the SPI module to use. */
    SPIPinout_t pinout;                /**< Routes the module to different pins on the MCU. */
    SPIMSTR_t masterSlave;             /**< Specifies master or slave. */
    SPICPOL_t clockPolarity;           /**< Specifies clock polarity. */
    SPICPHA_t clockPhase;              /**< Specifies clock phase. */
    SPILSBFE_t bitOrder;               /**< Specifies transmission endian. */
    SPIMODFEN_t faultMode;             /**< Enables or disables fault mode. */
    SPIBIDIROE_t bidirectionalMode;    /**< Sets bidirectional mode, MOMI/SISO or MOSI/MISO. */
    SPISPISWAI_t powerConservation;    /**< Sets the operation of clocks in wait mode. */
    SPISPC0_t bidirectionalPinControl; /**< Sets bidirectional mode, single-wire or normal. */
    uint32_t baudrate;                 /**< Sets the required baud-rate. */
} SPIModule_t;

/***************************************************************************//**
 * @brief Initialises the SPI module.
 * @param mod Description of the SPI module.
 ******************************************************************************/
void SPI_init(const SPIModule_t* const mod);

/***************************************************************************//**
 * @brief De-initialises the SPI module.
 * @param mod Description of the SPI module.
 ******************************************************************************/
void SPI_deinit(const SPIModule_t* const mod);

/***************************************************************************//**
 * @brief Enables or disables interrupts on a specific module.
 * @param mod Description of the SPI module.
 * @param spie Enables or disables interrupts globally for the SPI module.
 * @param sptie Enables or disables transmission interrupt.
 * @param mie Enables or disables match interrupt.
 ******************************************************************************/
void SPI_setupInterrupts(const SPIModule_t* const mod, const SPISPIE_t spie, const SPISPTIE_t sptie, const SPISPMIE_t mie);

/***************************************************************************//**
 * @brief Sends data on the SPI bus. This function is blocking.
 * @param mod Description of the SPI module.
 * @param value Byte to send.
 * @return The value returned from chip.
 ******************************************************************************/
uint8_t SPI_transfer(const SPIModule_t* const mod, uint8_t value);

/***************************************************************************//**
 * @brief Loads the match register, used for interrupt on match.
 * @param mod Description of the SPI module.
 * @param value Value to load to the match register.
 ******************************************************************************/
static inline void SPI_loadMatchRegister(const SPIModule_t* const mod, const uint8_t value)
{
    mod->base->M = value;
}

/** @} *//* end group */
