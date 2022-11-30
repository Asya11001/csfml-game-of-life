#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SFML/Graphics/RectangleShape.h>
#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include <stdbool.h>

#include "state_stack.h"
#include "state.h"
#include "../grid.h"

typedef struct GameState
{
	State* m_base;

	Grid* m_grid;

	void (*draw)(State* gameState);
	bool (*update)(State* gameState, sfTime deltaTime);
	bool (*handleEvent)(State* gameState, const sfEvent* event);
} GameState;

State* createGameState(StateStack* stateStack, Context context);
void deleteGameState(State* state);

void drawGameState(State* gameState);
bool updateGameState(State* gameState, sfTime deltaTime);
bool handleGameStateEvent(State* gameState, const sfEvent* event);

#endif
