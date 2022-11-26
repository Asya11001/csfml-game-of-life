#ifndef STATE_STRUCTURE_H
#define STATE_STRUCTURE_H

#include <SFML/Graphics/RenderWindow.h>

#include "state_identifiers.h"
#include "state_stack.h"

typedef struct Context
{ 
	sfRenderWindow* m_window;
} Context;

typedef struct State
{
	Context m_context;
	StateStack* m_stateStack;
} State;

State createState(Context context, StateStack* stateStack);
Context createContext(sfRenderWindow* window);

void requestStackPush(StateId id);
void requestStackPop();
void requestStackClear();

#endif
