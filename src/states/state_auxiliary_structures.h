#ifndef STATE_AUXILIARY_STRUCTURES_H
#define STATE_AUXILIARY_STRUCTURES_H

typedef struct State State;
typedef struct PendingChange PendingChange;

typedef struct PendingChangeArray
{
	int m_length;
	PendingChange* m_data;
} PendingChangeArray;

PendingChangeArray pendingChangeArrayCreate();
void pendingChangeArrayDestroy(PendingChangeArray* pendingChangeArray);

void pendingChangeArrayPushBack(PendingChangeArray* pendingChangeArray, PendingChange* change);
void pendingChangeArrayClear(PendingChangeArray* pendingChangeArray);

typedef struct StateArray
{
	int m_length;
	// array of pointers
	State** m_data;
} StateArray;

StateArray stateArrayCreate();
void stateArrayDestroy(StateArray* stateArray);

void stateArrayPushBack(StateArray* stateArray, State* state);
void stateArrayPopBack(StateArray* stateArray);
void stateArrayClear(StateArray* stateArray);

#endif
