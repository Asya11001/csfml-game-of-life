#ifndef STATE_STRUCTURE_H
#define STATE_STRUCTURE_H

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include <stdbool.h>

#include "state_identifiers.h"
#include "../grid.h"

typedef struct StateStack StateStack;
typedef struct State State;

typedef struct Context
{
	sfRenderWindow* m_window;
	// for game and pause states
	Grid* m_grid;
} Context;

typedef struct State
{
	void* m_derived;
	Context m_context;
	StateStack* m_stateStack;

	void (*requestStackPush)(State* state, StateId id);
	void (*requestStackPop)(State* state);
	void (*requestStackClear)(State* state);

	void (*draw)(State* state);
	bool (*update)(State* state, sfTime deltaTime);
	bool (*handleEvent)(State* state, const sfEvent* event);

	void (*deleteState)(State* state);
} State;

State* createNewState(StateStack* stateStack, Context context);
void deleteState(State* state);

Context createContext(sfRenderWindow* window, Grid* grid);

void requestStackPush(State* state, StateId id);
void requestStackPop(State* state);
void requestStackClear(State* state);

Context getContext(State* state);

#endif
