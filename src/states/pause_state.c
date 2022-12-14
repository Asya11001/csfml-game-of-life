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

	pauseState->m_grid = context.m_grid;

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
	//deleteGrid(derivedPart->m_grid);
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

bool updatePauseState(__attribute__((unused)) State* pauseState,
		__attribute__((unused)) sfTime deltaTime)
{
	return true;
}

bool handlePauseStateEvent(State* pauseState, const sfEvent* event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
	{
		pauseState->requestStackPop(pauseState);
		pauseState->requestStackPush(pauseState, game);
	}
	else if (event->type == sfEvtKeyPressed && event->key.code == sfKeyBackspace)
	{
		resetGridCellColors(pauseState->m_context.m_grid->m_cells,
				pauseState->m_context.m_grid->m_currentSize);
		pauseState->requestStackPop(pauseState);
		pauseState->requestStackPush(pauseState, menu);
	}

	return true;
}
