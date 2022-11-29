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
	gameState->m_grid = createGrid(10);

	// virtual functions:
	state->draw = drawGameState;
	state->update = updateGameState;
	state->handleEvent = handleGameStateEvent;

	return state;
}

void drawGameState(State* gameState)
{
	sfRenderWindow* window = getContext(gameState).m_window;
	// this is a nasty cast, i think it's necessary though
	GameState* derivedPart = (GameState*)gameState->m_derived;
	drawGrid(&derivedPart->m_grid, window);
}

bool updateGameState(State* gameState, sfTime deltaTime)
{
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
