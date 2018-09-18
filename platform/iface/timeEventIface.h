/** @file
 *  @defgroup timeEventIface.h timeEventIface.h
 *  @brief
 *
 *  Details for timeEventIface.h
 *
 *  @date 24 Aug 2018
 *  @author Andre Lundkvist
 *  @copyright Greenworks Tools Europe
 */

#pragma once

/** @addtogroup timeEventIface.h
  * @{ */

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint32_t timeSet_ms;
    uint32_t timeNow_ms;
    uint32_t expireTime_ms;
} TimeEvent_t;

void TimeEvent_init(void);
uint32_t TimeEvent_getClockTime(void);
void TimeEvent_start(TimeEvent_t* const ev, const int32_t timeout_ms);
bool TimeEvent_isExpired(TimeEvent_t* const ev);
uint32_t TimeEvent_getElapsedTime_ms(TimeEvent_t* const ev);

/** @} *//* end group */
