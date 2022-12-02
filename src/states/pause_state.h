#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include <stdbool.h>

#include "state_stack.h"
#include "../grid.h"

typedef struct PauseState
{
	State* m_base;

	Grid* m_grid;

	void (*draw)(State* pauseState);
	bool (*update)(State* pauseState, sfTime deltaTime);
	bool (*handleEvent)(State* pauseState, const sfEvent* event);
} PauseState;

State* createPauseState(StateStack* stateStack, Context context);
void deletePauseState(State* state);

void drawPauseState(State* pauseState);
bool updatePauseState(State* pauseState, sfTime deltaTime);
bool handlePauseStateEvent(State* pauseState, const sfEvent* event);

#endif
