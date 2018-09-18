/** @file
 *  @brief
 *
 *  Details for timeEvent.c
 *
 *  @date 24 Aug 2018
 *  @author Andre Lundkvist
 *  @copyright Greenworks Tools Europe
 */

#include "timeEventIface.h"
#include <stdint.h>
#include <stdbool.h>

#include "kexx_timer.h"

#define TIMEEVENT_TICKTIME_MS (1)

static void TimeEvent_updateClockTime(void);



static uint32_t clockTime_ms = 0;

/** @brief Periodic timer setup struct. */
static const PeriodicTimer_t timerTickSource = {
    .callback = TimeEvent_updateClockTime,
    .channel = 0,
};

void TimeEvent_init(void)
{
    /* Start the timer */
    PeriodicTimer_enableGlobal();
    PeriodicTimer_enableInterrupt(&timerTickSource, TIMEEVENT_TICKTIME_MS * 1000u);
}

uint32_t TimeEvent_getClockTime(void)
{
    return (clockTime_ms);
}

void TimeEvent_start(TimeEvent_t* const ev, const int32_t timeout_ms)
{
    ev->expireTime_ms = timeout_ms;
    ev->timeSet_ms = clockTime_ms;
    ev->timeNow_ms = clockTime_ms;
}

bool TimeEvent_isExpired(TimeEvent_t* const ev)
{
    ev->timeNow_ms = clockTime_ms;

    const bool isExpired = ((ev->timeNow_ms - ev->timeSet_ms) > ev->expireTime_ms) ? (true) : (false);

    return (isExpired);
}

uint32_t TimeEvent_getElapsedTime_ms(TimeEvent_t* const ev)
{
    ev->timeNow_ms = clockTime_ms;

    return (ev->timeNow_ms - ev->timeSet_ms);
}

static void TimeEvent_updateClockTime(void)
{
    clockTime_ms += TIMEEVENT_TICKTIME_MS;
}
