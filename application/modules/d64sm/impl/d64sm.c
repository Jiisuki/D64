/** @brief Implementation of the state machine.
 *
 *  Handles all state entry, exit and on cycle methods as well as transitions
 *  between events depending on incoming events.
 *
 *  @date 11 May 2018
 *  @author Andre Lundkvist
 *  @copyright Jiisuki Industries
 */

#include "d64smIface.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    D64SM_Event_t ev;
    void* targetState;
} D64SM_Transition_t;

#define MAX_OUTGOING_TRANSITIONS (4)

typedef struct
{
    D64SM_Transition_t transitionList[MAX_OUTGOING_TRANSITIONS];
    uint8_t numTransitions;
} D64SM_TransitionList_t;

typedef void (*D64SM_StateFcn_t)(void);

typedef struct
{
    bool isActive;
    D64SM_StateFcn_t entryFcn;
    D64SM_StateFcn_t exitFcn;
    D64SM_StateFcn_t onCycleFcn;
    D64SM_TransitionList_t outgoingTr;
} D64SM_State_t;

#define EVENT_BUFFER_SIZE (8)

typedef struct
{
    D64SM_Event_t ev[EVENT_BUFFER_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t numEvents;
} D64SM_EventBuffer_t;

typedef struct
{
    struct
    {
        D64SM_State_t deviceClosed;
        D64SM_State_t deviceOpen;
        D64SM_State_t closingChannels;
        D64SM_State_t storeData;
        D64SM_State_t readFilename;
        D64SM_State_t deviceTalker;
        D64SM_State_t searchFilename;
        D64SM_State_t sendDirectory;
        D64SM_State_t sendData;
        D64SM_State_t error;
    } state;

    D64SM_State_t* currentState;
    D64SM_EventBuffer_t evBuffer;
} D64SM_t;

static D64SM_t self;

/* Local prototypes. */
static void processEvent(const D64SM_Event_t ev);
static void initState(D64SM_State_t* const state, D64SM_StateFcn_t const entry, D64SM_StateFcn_t const exit, D64SM_StateFcn_t const onCycle);
static void addTransition(D64SM_State_t* const state, const D64SM_Event_t ev, const D64SM_State_t* const targetState);
static void initEventBuffer(D64SM_EventBuffer_t* const buffer);
static bool addEvent(D64SM_EventBuffer_t* const buffer, const D64SM_Event_t ev);
static bool popEvent(D64SM_EventBuffer_t* const buffer, D64SM_Event_t* const ev);

void D64SM_init(void)
{
    initState(&self.state.deviceClosed, NULL, NULL, NULL);
    initEventBuffer(&self.evBuffer);

    addTransition(&self.state.deviceClosed, D64SM_Event_Listen, (void*) &self.state.deviceOpen);
    addTransition(&self.state.deviceClosed, D64SM_Event_Talk, (void*) &self.state.deviceTalker);

    addTransition(&self.state.deviceOpen, D64SM_Event_Close, (void*) &self.state.closingChannels);
    addTransition(&self.state.deviceOpen, D64SM_Event_OpenDat, (void*) &self.state.storeData);
    addTransition(&self.state.deviceOpen, D64SM_Event_Open, (void*) &self.state.readFilename);
    addTransition(&self.state.deviceOpen, D64SM_Event_Unlisten, (void*) &self.state.deviceClosed);

    addTransition(&self.state.storeData, D64SM_Event_EOI, (void*) &self.state.deviceOpen);

    addTransition(&self.state.readFilename, D64SM_Event_EOI, (void*) &self.state.deviceOpen);

    addTransition(&self.state.deviceTalker, D64SM_Event_OpenDat, (void*) &self.state.searchFilename);
    addTransition(&self.state.deviceTalker, D64SM_Event_Untalk, (void*) &self.state.deviceClosed);

    addTransition(&self.state.searchFilename, D64SM_Event_FileFound, (void*) &self.state.sendData);
    addTransition(&self.state.searchFilename, D64SM_Event_SpecialFilename, (void*) &self.state.sendDirectory);
    addTransition(&self.state.searchFilename, D64SM_Event_FileNotFound, (void*) &self.state.error);

    addTransition(&self.state.sendData, D64SM_Event_EOI, (void*) &self.state.deviceTalker);
    addTransition(&self.state.sendData, D64SM_Event_AtnRequest, (void*) &self.state.deviceClosed);

    addTransition(&self.state.sendDirectory, D64SM_Event_EOI, (void*) &self.state.deviceTalker);
    addTransition(&self.state.sendDirectory, D64SM_Event_AtnRequest, (void*) &self.state.deviceClosed);
}

void D64SM_raiseEvent(const D64SM_Event_t ev)
{
    if (!addEvent(&self.evBuffer, ev))
    {
        /* Error! */
    }
}

void D64SM_runCycle(void)
{
    if (self.currentState->onCycleFcn)
    {
        self.currentState->onCycleFcn();
    }

    D64SM_Event_t ev;
    bool result = popEvent(&self.evBuffer, &ev);

    if (result)
    {
        processEvent(ev);
    }
}

static void processEvent(const D64SM_Event_t ev)
{
    for (uint8_t i = 0; i < self.currentState->outgoingTr.numTransitions; i++)
    {
        if (ev == self.currentState->outgoingTr.transitionList[i].ev)
        {
            if (self.currentState->outgoingTr.transitionList[i].targetState)
            {
                self.currentState->exitFcn();
                self.currentState = self.currentState->outgoingTr.transitionList[i].targetState;
                self.currentState->entryFcn();
            }
        }
    }
}

static void initState(D64SM_State_t* const state, D64SM_StateFcn_t const entry, D64SM_StateFcn_t const exit, D64SM_StateFcn_t const onCycle)
{
    state->entryFcn = entry;
    state->exitFcn = exit;
    state->onCycleFcn = onCycle;
    state->isActive = false;
}

static void addTransition(D64SM_State_t* const state, const D64SM_Event_t ev, const D64SM_State_t* const targetState)
{
    if (state->outgoingTr.numTransitions < MAX_OUTGOING_TRANSITIONS)
    {
        D64SM_Transition_t* const tr = &state->outgoingTr.transitionList[state->outgoingTr.numTransitions];
        tr->ev = ev;
        tr->targetState = (void*) targetState;

        state->outgoingTr.numTransitions++;
    }
}

static void initEventBuffer(D64SM_EventBuffer_t* const buffer)
{
    for (uint8_t i = 0; i < EVENT_BUFFER_SIZE; i++)
    {
        buffer->ev[i] = 0;
    }
    buffer->head = 0;
    buffer->tail = 0;
    buffer->numEvents = 0;
}

static bool addEvent(D64SM_EventBuffer_t* const buffer, const D64SM_Event_t ev)
{
    if (buffer->numEvents < EVENT_BUFFER_SIZE)
    {
        buffer->ev[buffer->head] = ev;
        buffer->head = (buffer->head + 1) % EVENT_BUFFER_SIZE;
        return (true);
    }

    return (false);
}

static bool popEvent(D64SM_EventBuffer_t* const buffer, D64SM_Event_t* const ev)
{
    if (buffer->numEvents > 0)
    {
        *ev = buffer->ev[buffer->tail];
        buffer->tail = (buffer->tail + 1) % EVENT_BUFFER_SIZE;
        return (true);
    }

    return (false);
}
