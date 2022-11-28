#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include <stdbool.h>

#include "state_stack.h"

typedef struct TitleState TitleState;

typedef struct TitleState
{
	State* m_base;

	void (*draw)(TitleState* titleState);
	bool (*update)(TitleState* titleState, sfTime deltaTime);
	bool (*handleEvent)(TitleState* titleState, const sfEvent* event);
} TitleState;

State* createTitleState(StateStack* stateStack, Context context);
void destroyTitleState(State* state);

void drawTitleState(TitleState* titleState);
bool udpateTitleState(TitleState* titleState, sfTime deltaTime);
bool handleTitleStateEvent(TitleState* titleState, const sfEvent* event);

#endif
