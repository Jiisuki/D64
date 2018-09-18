/** @file
 *  @defgroup SYSTICK Systick Handler
 *  @ingroup KEXX
 *  @brief Implements the Systick handler and option to register a callback.
 */

#pragma once

/** @addtogroup SYSTICK
  * @{ */

#include <stdint.h>

/** @brief Callback function for Systick interrupt. */
typedef void (*Systick_CallbackFcn_t)(void);

/***************************************************************************//**
 * @brief Initialises the Systick interrupt with a provided periodic time.
 * @param time_us Periodic interrupt time in microseconds.
 ******************************************************************************/
void Systick_init(uint32_t time_us);

/***************************************************************************//**
 * @brief Registers an interrupt callback.
 * @param callback Function pointer to the callback.
 ******************************************************************************/
void Systick_registerCallback(const Systick_CallbackFcn_t const callback);

/** @} *//* end group */
