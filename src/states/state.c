#include "state.h"
#include "state_stack.h"

#include <stdlib.h>
#include <stdio.h>

State* createNewState(StateStack* stateStack, Context context)
{
	State* state = malloc(sizeof(State));
	// point to itself since we are creating the base struct object
	state->m_derived = state;
	state->m_stateStack = stateStack;
	state->m_context = context;

	state->requestStackPush = requestStackPush;
	state->requestStackPop = requestStackPop;
	state->requestStackClear = requestStackClear;

	// destructor:
	state->deleteState = deleteState;

	return state;
}

void deleteState(State* state)
{
	free(state);
	state = NULL;
}

Context createContext(sfRenderWindow* window)
{
	Context context = { window };
	return context;
}

void requestStackPush(State* state, StateId id)
{
	pushStateToStack(state->m_stateStack, id);
}

void requestStackPop(State* state)
{
	popStateFromStack(state->m_stateStack);
}

void requestStackClear(State* state)
{
	clearStateStack(state->m_stateStack);
}

Context getContext(State* state)
{
	return state->m_context;
}
