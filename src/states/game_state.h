#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include <stdbool.h>

#include "state_stack.h"

typedef struct GameState
{
	State* m_base;

	void (*draw)(State* gameState);
	bool (*update)(State* gameState, sfTime deltaTime);
	bool (*handleEvent)(State* gameState, const sfEvent* event);
} GameState;

State* createGameState(StateStack* stateStack, Context context);
void destroyGameState(State* state);

void drawGameState(State* gameState);
bool updateGameState(State* gameState, sfTime deltaTime);
bool handleGameStateEvent(State* gameState, const sfEvent* event);

#endif
