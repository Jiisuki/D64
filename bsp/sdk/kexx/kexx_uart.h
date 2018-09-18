/** @file
 *  @defgroup UART UART Driver
 *  @ingroup KEXX
 *  @brief UART driver implementation.
 */

#pragma once

/** @addtogroup UART
 *  @{ */

#include <mcu.h>

/** @brief Callback function pointer type. */
typedef uint32_t (*UARTCallbackFcn_t)(void);

/** @brief Describes the routing of the UART module to MCU pins. */
typedef enum
{
    kUART_PS0 = 0U, /**< UART_0 TX/RX = PTB1/PTB0, UART_1 TX/RX = PTC7/PTC6, UART_2 TX/RX = PTD7/PTD6 */
    kUART_PS1 = 1U, /**< UART_0 TX/RX = PTA3/PTA2, UART_1 TX/RX = PTF3/PTF2, UART_2 TX/RX = PTI1/PTI0 */
} UARTPinout_t;

/** @brief Selects UART parity. */
typedef enum
{
    kUART_NO_PARITY = 0U, /**< No parity is used. */
    kUART_ODD = 3U,       /**< Odd parity is used. */
    kUART_EVEN = 2U,      /**< Even parity is used. */
} UARTParityBits_t;

/** @brief Selects the number of bits. */
typedef enum
{
    kUART_8bit = 0U, /**< 8-bit transmission. */
    kUART_9bit = 1U, /**< 9-bit transmission. */
} UARTBits_t;

/** @brief Selects TX polarity. */
typedef enum
{
    kUART_TXINV_INVERT = 1U,        /**< Invert TX output. */
    kUART_TXINV_DO_NOT_INVERT = 0U, /**< Do not invert TX output. */
} UARTInvertTx_t;

typedef enum
{
    kUART_RXINV_INVERT = 1u,
    kUART_RXINV_DO_NOT_INVERT = 0u,
} UARTInvertRx_t;

typedef enum
{
    kUART_SBNS_ONE_STOP_BIT = 0u,
    kUART_SBNS_TWO_STOP_BITS = 1u,
} UARTStopBits_t;

typedef enum
{
    kUART_INTERRUPT_DISABLE = 0u,
    kUART_INTERRUPT_ENABLE_TX = 1u,
    kUART_INTERRUPT_ENABLE_TX_COMPLETE = 2u,
    kUART_INTERRUPT_ENABLE_RX = 4u,
    kUART_INTERRUPT_ENABLE_IDLE = 8u,
} UARTInterrupt_t;

/** @brief Description of the UART module. */
typedef struct
{
    UART_Type* base;            /**< Base address to the UART module. */
    UARTPinout_t pinout;        /**< Routing of the UART to the MCU pins. */
    uint32_t baudrate;          /**< Specifies the UART baud. */
    UARTParityBits_t parity;    /**< Specifies the UART parity setting. */
    UARTBits_t mode;            /**< Specifies the UART mode, i.e. number of bits in a byte. */
    UARTStopBits_t stopBits;    /**< Specifies the UART stop bits. */
    UARTInvertTx_t invertTx;    /**< Specifies UART TX polarity. */
    UARTInvertRx_t invertRx;    /**< Specifies UART RX polarity. */
    UARTCallbackFcn_t callback; /**< Callback function for interrupt driven UART. */
    UARTInterrupt_t irq;        /**< Initial interrupt settings. */
} UARTModule_t;

/***************************************************************************//**
 * @brief Controls interrupt settings for UART.
 *
 * The irq settings can be bitmasked together in order to enable several things.
 * Make sure to handle everything in the callback function.
 *
 * @code
 * UART_interruptControl(&myCom, kUART_INTERRUPT_ENABLE_RX | kUART_INTERRUPT_ENABLE_IDLE);
 * @endcode
 *
 * @param mod Reference to the UART module configuration.
 * @param irq Interrupt settings, i.e. what to enable interrupts for.
 ******************************************************************************/
void UART_interruptControl(const UARTModule_t* const mod, const UARTInterrupt_t irq);

/***************************************************************************//**
 * @brief Initialises the UART.
 * @param mod Description of the UART module.
 ******************************************************************************/
void UART_init(const UARTModule_t* const mod);

/***************************************************************************//**
 * @brief Transmits a string on a given UART module.
 * @param umod UART specification.
 * @param string The string to transmit.
 * @param len Length of the string.
 ******************************************************************************/
void UART_transmitBlocking(const UARTModule_t* const umod, const uint8_t *string, uint32_t len);

/***************************************************************************//**
 * @brief Enables transmission on the UART.
 * @param mod Description of the UART.
 ******************************************************************************/
static inline void UART_enableTX(const UARTModule_t* const mod)
{
    mod->base->C2 |= UART_C2_TE_MASK;
}

/***************************************************************************//**
 * @brief Disables transmission on the UART.
 * @param mod Description of the UART.
 ******************************************************************************/
static inline void UART_disableTX(const UARTModule_t* const mod)
{
    mod->base->C2 &= (~UART_C2_TE_MASK);
}

/***************************************************************************//**
 * @brief Enables reception on the UART.
 * @param mod Description of the UART.
 ******************************************************************************/
static inline void UART_enableRX(const UARTModule_t* const mod)
{
    mod->base->C2 |= UART_C2_RE_MASK;
}

/***************************************************************************//**
 * @brief Disables reception on the UART.
 * @param mod Description of the UART.
 ******************************************************************************/
static inline void UART_disableRX(const UARTModule_t* const mod)
{
    mod->base->C2 &= (~UART_C2_RE_MASK);
}

/** @} *//* end group */

