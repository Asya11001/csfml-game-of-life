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

	// virtual functions:
	state->draw = drawGameState;
	state->update = updateGameState;
	state->handleEvent = handleGameStateEvent;

	return state;
}

void drawGameState(State* gameState)
{
	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, 100.0f);
	sfCircleShape_setFillColor(circle, sfMagenta);
	Context context = getContext(gameState);
	sfRenderWindow_drawCircleShape(context.m_window, circle, NULL);
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
