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
