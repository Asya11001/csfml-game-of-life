#ifndef STATE_STRUCTURE_H
#define STATE_STRUCTURE_H

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include "state_identifiers.h"

typedef struct StateStack StateStack;
typedef enum StateId StateId;
typedef struct State State;

typedef struct Context
{
	sfRenderWindow* m_window;
} Context;

typedef struct State
{
	void* m_derived;
	Context m_context;
	StateStack* m_stateStack;

	void (*requestStackPush)(State* state, StateId id);
	void (*requestStackPop)(State* state);
	void (*requestStackClear)(State* state);
} State;

State* createNewState(StateStack* stateStack, Context context);
Context createContext(sfRenderWindow* window);

void requestStackPush(State* state, StateId id);
void requestStackPop(State* state);
void requestStackClear(State* state);

Context getContext(State* state);

#endif
