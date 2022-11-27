#ifndef STATE_AUXILIARY_STRUCTURES_H
#define STATE_AUXILIARY_STRUCTURES_H

struct State;
typedef struct State State;
struct PendingChange;
typedef struct PendingChange PendingChange;

// to-do:
// vector of state pointers (title state, menu state, pause state and game state)
// vector of pending changes that get applied in the applyPendingChanges function in the state

typedef struct PendingChangeArray
{

} PendingChangeArray;

typedef struct StateArray
{
	int m_length;
	State* m_data;
} StateArray;

void stateArray_push_back(StateArray* stateArray, State* state);
void stateArray_pop_back(StateArray* stateArray);
void stateArray_clear(StateArray* stateArray);

void stateArray_resize(StateArray* stateArray, int newLength);

#endif
