#include "pause_state.h"

#include <SFML/Graphics/CircleShape.h>

#include <stdlib.h>

State* createPauseState(StateStack* stateStack, Context context)
{
	// construct base class
	State* state = createNewState(stateStack, context);
	// construct the derived class
	PauseState* pauseState = malloc(sizeof(PauseState));

	state->m_derived = pauseState;

	pauseState->m_grid = createNewGrid(10);

	// virtual functions:
	state->draw = drawPauseState;
	state->update = updatePauseState;
	state->handleEvent = handlePauseStateEvent;

	// virtual destructor:
	state->deleteState = deletePauseState;

	return state;
}

void deletePauseState(State* state)
{
	// derived destructor:
	PauseState* derivedPart = (PauseState*)state->m_derived;
	deleteGrid(derivedPart->m_grid);
	free(derivedPart);
	// base destructor:
	deleteState(state);
}

void drawPauseState(State* pauseState)
{
	sfRenderWindow* window = getContext(pauseState).m_window;
	PauseState* derivedPart = (PauseState*)pauseState->m_derived;
	drawGrid(derivedPart->m_grid, window);
}

bool updatePauseState(State* pauseState, sfTime deltaTime)
{
	return true;
}

bool handlePauseStateEvent(State* pauseState, const sfEvent* event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
	{
		// removing this might cause bad memory access
		pauseState->requestStackPop(pauseState);
		pauseState->requestStackPush(pauseState, game);
	}
	else if (event->type == sfEvtKeyPressed && event->key.code == sfKeyBackspace)
	{
		pauseState->requestStackPop(pauseState);
		pauseState->requestStackPush(pauseState, menu);
	}

	return true;
}
