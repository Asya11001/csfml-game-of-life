#include "state.h"

State createState(Context context, StateStack* stateStack)
{
	State state;
	state.m_context = context;
	state.m_stateStack = stateStack;
}

Context createContext(sfRenderWindow* window)
{
	Context context;
	context.m_window = window;
}

void requestStackPush(State* state, enum StateId id)
{
	pushState(state->m_stateStack, id);
}

void requestStackPop(State* state)
{
	popState(state->m_stateStack);
}

void requestStackClear(State* state)
{
	clearState(state->m_stateStack);
}
