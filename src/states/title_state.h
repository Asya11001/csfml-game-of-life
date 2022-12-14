#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include <stdbool.h>

#include "state_stack.h"

typedef struct TitleState
{
	State* m_base;

	void (*draw)(State* titleState);
	bool (*update)(State* titleState, sfTime deltaTime);
	bool (*handleEvent)(State* titleState, const sfEvent* event);
} TitleState;

State* createTitleState(StateStack* stateStack, Context context);
void deleteTitleState(State* state);

void drawTitleState(State* titleState);
bool updateTitleState(State* titleState, sfTime deltaTime);
bool handleTitleStateEvent(State* titleState, const sfEvent* event);

#endif
