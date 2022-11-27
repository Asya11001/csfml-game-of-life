#include "state.h"
#include "state_stack.h"

State createState(Context context, StateStack* stateStack)
{
	State state = { context, stateStack };
	return state;
}

Context createContext(sfRenderWindow* window)
{
	Context context = { window };

	return context;
}

void requestStackPush(State* state, StateId id)
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
