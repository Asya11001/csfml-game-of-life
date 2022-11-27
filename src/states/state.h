#ifndef STATE_STRUCTURE_H
#define STATE_STRUCTURE_H

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include "state_identifiers.h"

struct StateStack;

typedef struct Context
{
	sfRenderWindow* m_window;
} Context;

typedef struct State
{
	Context m_context;
	struct StateStack* m_stateStack;

	// abstract functions
	void (*draw)(void);
	void (*update)(sfTime deltaTime);
	void (*handleEvent)(const sfEvent* event);
} State;

State createState(Context context, struct StateStack* stateStack);
Context createContext(sfRenderWindow* window);

void requestStackPush(State* state, enum StateId id);
void requestStackPop(State* state);
void requestStackClear(State* state);

Context getContext(State* state);

#endif
