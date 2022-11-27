#ifndef STATE_STRUCTURE_H
#define STATE_STRUCTURE_H

#include <SFML/Graphics/RenderWindow.h>

#include "state_identifiers.h"
#include <stdalign.h>

struct StateStack;

typedef struct Context
{
	sfRenderWindow* m_window;
} Context;

typedef struct State
{
	Context m_context;
	struct StateStack* m_stateStack;
} State;

State createState(Context context, struct StateStack* stateStack);
Context createContext(sfRenderWindow* window);

void requestStackPush(State* state, enum StateId id);
void requestStackPop(State* state);
void requestStackClear(State* state);

#endif
