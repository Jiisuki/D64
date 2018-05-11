/** @brief Interface of the state machine.
 *
 *  Handles all state entry, exit and on cycle methods as well as transitions
 *  between events depending on incoming events.
 *
 *  @date 11 May 2018
 *  @author Andre Lundkvist
 *  @copyright Jiisuki Industries
 */

#pragma once

typedef enum
{
    D64SM_Event_Listen,
    D64SM_Event_Unlisten,
    D64SM_Event_Talk,
    D64SM_Event_Untalk,
    D64SM_Event_OpenDat,
    D64SM_Event_Close,
    D64SM_Event_Open,
    D64SM_Event_EOI,
    D64SM_Event_FileFound,
    D64SM_Event_FileNotFound,
    D64SM_Event_SpecialFilename,
    D64SM_Event_AtnRequest,
} D64SM_Event_t;

void D64SM_init(void);
void D64SM_runCycle(void);
void D64SM_raiseEvent(const D64SM_Event_t ev);
