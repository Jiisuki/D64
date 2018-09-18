
#include "smIface.h"

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void SM_initState(SM_State_t* const state, const int32_t id, const SM_Enact_t enact, const SM_OnCycle_t oncycle, const SM_Exact_t exact)
{
    state->id = id;
    state->enact = enact;
    state->oncycle = oncycle;
    state->exact = exact;
}

void SM_initTr(SM_Transition_t* const tr, SM_State_t* const out, SM_Event_t* const ev, SM_State_t* const in)
{
    tr->out = out;
    tr->in = in;
    tr->ev = ev;
}

/** @brief Initialises the state machine.
 *  @param sm Pointer to the state machine.
 *  @param entryState Pointer to the initial entry state.
 *  @param transitions Array of all possible state transitions.
 *  @param numTransitions Number of transitions provided.
 */
void SM_init(SM_t* const sm, SM_State_t* const entryState, SM_Transition_t* const transitions, const uint32_t numTransitions)
{
    // Initialise the state machine transitions and enter the entry state.
	sm->state = entryState;
	sm->transitions = transitions;
	sm->numTransitions = numTransitions;

    // If the state is valid..
	if (sm->state)
	{
        // .. and has an entry action ..
		if (sm->state->enact)
		{
            // .. run the entry action function.
			sm->state->enact(0);
		}
	}
}

static void SM_clearInEvents(SM_t* const sm)
{
    for (uint8_t i = 0; i < sm->numTransitions; i++)
    {
        SM_clearEv(sm->transitions[i].ev);
    }
}

/** @brief Runs the state machine.
 *  @param sm Pointer to the state machine.
 */
void SM_run(SM_t* const sm)
{
    // If the current state has oncycle function ..
	if (sm->state->oncycle)
	{
        // .. run the function.
		sm->state->oncycle();
	}

    // Check all state transitions.
	for (uint32_t i = 0; i < sm->numTransitions; i++)
	{
		SM_Transition_t* const tr = &sm->transitions[i];

        // If the transition has a valid event..
		if (tr->ev)
		{
            // .. and the event is raised ..
			if (tr->ev->raised)
			{
                // .. and the transition out state corresponds to the active state ..
				if (sm->state == tr->out)
				{
                    // .. perform the transition.
					if (sm->state->exact)
					{
						sm->state->exact(tr->ev);
					}

					if (tr->in)
					{
						sm->state = (SM_State_t*)tr->in;
					}

					if (sm->state->enact)
					{
						sm->state->enact(tr->ev);
					}

                    // We've used the transition, clear it and finish.
					SM_clearEv(tr->ev);
					return;
				}
                else
                {
                    // It's not usable for us, just skip it.
                }
			}
		}
	}

	SM_clearInEvents(sm);
}

void SM_raiseEv(SM_Event_t* const ev, const void* const data, const size_t s)
{
	if (ev)
	{
		ev->raised = true;

		if ((data) && (s))
		{
		    ev->size = s;
		    ev->data = malloc(s);
		    if (ev->data)
		    {
		        memcpy(ev->data, data, s);
		    }
		}
	}
}

void SM_clearEv(SM_Event_t* const ev)
{
	if (ev)
	{
		ev->raised = false;
		if (ev->data)
		{
		    free(ev->data);
		    ev->size = 0;
		}
	}
}

void SM_initEv(SM_Event_t* const ev, const int32_t id)
{
    if (ev)
    {
        ev->raised = false;
        ev->data = (void*) 0;
        ev->size = 0;
        ev->id = id;
    }
}

bool SM_evDataCmp(const SM_Event_t* const ev, const size_t size)
{
    bool result = false;

    if (ev)
    {
        if ((ev->data) && (size == ev->size))
        {
            result = true;
        }
    }

    return (result);
}

bool SM_evCmp(const SM_Event_t* const ev, const int32_t id)
{
    bool result = false;

    if (ev)
    {
        if (id == ev->id)
        {
            result = true;
        }
    }

    return (result);
}

