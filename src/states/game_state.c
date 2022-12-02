#include "game_state.h"

#include <SFML/Graphics/CircleShape.h>

#include <stdlib.h>

State* createGameState(StateStack* stateStack, Context context)
{
	// construct base class
	State* state = createNewState(stateStack, context);
	// construct the derived class
	GameState* gameState = malloc(sizeof(GameState));

	state->m_derived = gameState;

	// initialize derived class memebers
	gameState->m_grid = createNewGrid(10);

	// virtual functions:
	state->draw = drawGameState;
	state->update = updateGameState;
	state->handleEvent = handleGameStateEvent;

	// virtual destructor:
	state->deleteState = deleteGameState;

	return state;
}

void deleteGameState(State* state)
{
	// derived destructor
	GameState* derivedPart = (GameState*)state->m_derived;
	deleteGrid(derivedPart->m_grid);
	free(derivedPart);
	// base destructor
	deleteState(state);
}

void drawGameState(State* gameState)
{
	sfRenderWindow* window = getContext(gameState).m_window;
	GameState* derivedPart = (GameState*)gameState->m_derived;
	drawGrid(derivedPart->m_grid, window);
}

bool updateGameState(State* gameState, sfTime deltaTime)
{
	GameState* derivedPart = (GameState*)gameState->m_derived;
	updateGrid(derivedPart->m_grid, deltaTime);
	return true;
}

bool handleGameStateEvent(State* gameState, const sfEvent* event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
	{
		gameState->requestStackPop(gameState);
		gameState->requestStackPush(gameState, pause);
	}

	return true;
}
