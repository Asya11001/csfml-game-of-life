#ifndef MENU_STATE_H
#define MENU_STATE_H

#include <SFML/System/Time.h>
#include <SFML/Window/Event.h>

#include <stdbool.h>

#include "state_stack.h"

typedef struct MenuState
{
	State* m_base;

	void (*draw)(State* menuState);
	bool (*update)(State* menuState, sfTime deltaTime);
	bool (*handleEvent)(State* menuState, const sfEvent* event);
} MenuState;

State* createMenuState(StateStack* stateStack, Context context);
void destroyMenuState(State* state);

void drawMenuState(State* menuState);
bool updateMenuState(State* menuState, sfTime deltaTime);
bool handleMenuStateEvent(State* menuState, const sfEvent* event);

#endif
