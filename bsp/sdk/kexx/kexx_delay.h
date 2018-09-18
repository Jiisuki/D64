/** @file
 *  @defgroup kexx_delay.h kexx_delay.h
 *  @brief 
 *
 *  ASM implementation of a blocking delay function.
 */

#pragma once

/** @addtogroup kexx_delay.h
  * @{ */

/***************************************************************************//**
 * @brief Blocks execution for specific time in clock ticks.
 *
 * To get a wait time in nanoseconds:
 * time_ticks = (sysclk * time_us) / 1000000000
 *
 * To get a wait time in microseconds:
 * time_ticks = (sysclk * time_ns) / 1000000
 *
 * To get a wait time in milliseconds:
 * time_ticks = (sysclk * time_ms) / 1000
 *
 * @param time_ticks The time to wait (in sysclk ticks).
 ******************************************************************************/
extern void Delay_ticks(uint32_t time_ticks);

/** @} *//* end group */
