#ifndef STATE_AUXILIARY_STRUCTURES_H
#define STATE_AUXILIARY_STRUCTURES_H

#include "state_identifiers.h"

typedef struct State State;
typedef struct PendingChange PendingChange;

typedef struct PendingChangeArray
{
	int m_length;
	PendingChange* m_data;
} PendingChangeArray;

PendingChangeArray pendingChangeArrayCreate(void);
void pendingChangeArrayDestroy(PendingChangeArray* pendingChangeArray);

void pendingChangeArrayPushBack(PendingChangeArray* pendingChangeArray, const PendingChange* change);
void pendingChangeArrayClear(PendingChangeArray* pendingChangeArray);
PendingChange pendingChangeArrayGet(const PendingChangeArray* pendingChangeArray, int index);

typedef struct StateArray
{
	int m_length;
	// array of pointers
	State** m_data;
} StateArray;

StateArray stateArrayCreate(void);
void stateArrayDestroy(StateArray* stateArray);

void stateArrayPushBack(StateArray* stateArray, State* state);
void stateArrayPopBack(StateArray* stateArray);
void stateArrayClear(StateArray* stateArray);
State* stateArrayGet(StateArray* stateArray, int index);

#endif
