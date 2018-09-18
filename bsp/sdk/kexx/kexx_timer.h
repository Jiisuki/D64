/** @file
 *  @defgroup PIT PIT Driver
 *  @ingroup KEXX
 *  @brief PIT - Periodic Interrupt Timer driver implementation.
 */

#pragma once

/** @addtogroup PIT
 *  @{ */

#include <mcu.h>
#include <stdint.h>
#include <stdlib.h>

/** @brief Callback type for timeout event. */
typedef void (*PeriodicTimerCallbackFcn_t)(void);

/** @brief Description of the peripheral interrupt timer. */
typedef struct
{
    uint8_t channel; /**< PIT timer channel. */
    PeriodicTimerCallbackFcn_t callback; /**< Callback function for interrupt driven timer. */
} PeriodicTimer_t;

/***************************************************************************//**
 * @brief Enables the PIT module globally.
 ******************************************************************************/
void PeriodicTimer_enableGlobal(void);

/***************************************************************************//**
 * @brief Disables the PIT module globally.
 ******************************************************************************/
void PeriodicTimer_disableGlobal(void);

/***************************************************************************//**
 * @brief Enables the timer.
 *
 * @param timer Description of the timer.
 ******************************************************************************/
void PeriodicTimer_enable(const PeriodicTimer_t* const timer);

/***************************************************************************//**
 * @brief Disables the timer.
 *
 * @param timer Description of the timer.
 ******************************************************************************/
void PeriodicTimer_disable(const PeriodicTimer_t* const timer);

/***************************************************************************//**
 * @brief Enables the timer and waits until it times out before it returns.
 *
 * This function is not super exact, and can be something like 30 microseconds
 * off.
 *
 * @param timer Description of the timer.
 * @param us Wait time in microseconds.
 ******************************************************************************/
void PeriodicTimer_wait(const PeriodicTimer_t* const timer, const uint32_t us);

/***************************************************************************//**
 * @brief Checks the interrupt flag on the timer.
 *
 * @param timer Description of the timer.
 * @return Timer interrupt flag.
 ******************************************************************************/
uint8_t PeriodicTimer_checkFlag(const PeriodicTimer_t* const timer);

/***************************************************************************//**
 * @brief Clears the interrupt flag.
 *
 * @param timer Description of the timer.
 ******************************************************************************/
void PeriodicTimer_clearFlag(const PeriodicTimer_t* const timer);

/***************************************************************************//**
 * @brief Enables timer interrupt on timeout.
 *
 * @param timer Description of the timer.
 * @param us Wait time in microseconds.
 ******************************************************************************/
void PeriodicTimer_enableInterrupt(const PeriodicTimer_t* const timer, const uint32_t us);

/***************************************************************************//**
 * @brief Disables timer interrupt on timeout.
 *
 * @param timer Description of the timer.
 ******************************************************************************/
void PeriodicTimer_disableInterrupt(const PeriodicTimer_t* const timer);

/** @} *//* end group */

