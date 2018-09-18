#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
	bool raised;
	void* data;
	size_t size;
	int32_t id;
} SM_Event_t;

typedef struct
{
	SM_Event_t* ev;
	void* out;
	void* in;
} SM_Transition_t;

typedef void(*SM_Enact_t)(const SM_Event_t* const ev);
typedef void(*SM_Exact_t)(const SM_Event_t* const ev);
typedef void(*SM_OnCycle_t)(void);

typedef struct
{
	SM_Enact_t enact;
	SM_OnCycle_t oncycle;
	SM_Exact_t exact;
	int32_t id;
} SM_State_t;

typedef struct
{
	SM_State_t* state;
	SM_Transition_t* transitions;
	uint32_t numTransitions;
} SM_t;

void SM_initState(SM_State_t* const state, const int32_t id, const SM_Enact_t enact, const SM_OnCycle_t oncycle, const SM_Exact_t exact);

void SM_initTr(SM_Transition_t* const tr, SM_State_t* const out, SM_Event_t* const ev, SM_State_t* const in);

void SM_init(SM_t* const sm, SM_State_t* const entryState, SM_Transition_t* const transitions, const uint32_t numTransitions);

void SM_run(SM_t* const sm);

void SM_raiseEv(SM_Event_t* const ev, const void* const data, const size_t s);

void SM_clearEv(SM_Event_t* const ev);

void SM_initEv(SM_Event_t* const ev, const int32_t id);

bool SM_evDataCmp(const SM_Event_t* const ev, const size_t size);

bool SM_evCmp(const SM_Event_t* const ev, const int32_t id);

