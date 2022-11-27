#ifndef STATE_AUXILIARY_STRUCTURES_H
#define STATE_AUXILIARY_STRUCTURES_H

typedef struct State State;
typedef struct PendingChange PendingChange;

typedef struct PendingChangeArray
{
	int m_length;
	PendingChange* m_data;
} PendingChangeArray;

PendingChangeArray pendingChangeArray_create();
void pendingChangeArray_destroy(PendingChangeArray* pendingChangeArray);

void pendingChangeArray_push_back(PendingChangeArray* pendingChangeArray, PendingChange* change);
void pendingChangeArray_clear(PendingChangeArray* pendingChangeArray);

typedef struct StateArray
{
	int m_length;
	// array of pointers
	State** m_data;
} StateArray;

StateArray stateArray_create();
void stateArray_destroy(StateArray* stateArray);

void stateArray_push_back(StateArray* stateArray, State* state);
void stateArray_pop_back(StateArray* stateArray);
void stateArray_clear(StateArray* stateArray);

#endif
