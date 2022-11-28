#include "menu_state.h"

#include <SFML/Graphics/CircleShape.h>

#include <stdlib.h>

State* createMenuState(StateStack* stateStack, Context context)
{
	// construct base class
	State* state = createNewState(stateStack, context);
	// construct the derived class
	MenuState* menuState = malloc(sizeof(MenuState));

	state->m_derived = menuState;

	// virtual functions:
	state->draw = drawMenuState;
	state->update = updateMenuState;
	state->handleEvent = handleMenuStateEvent;

	return state;
}

void drawMenuState(State* menuState)
{
	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, 100.0f);
	sfCircleShape_setFillColor(circle, sfGreen);
	Context context = getContext(menuState);
	sfRenderWindow_drawCircleShape(context.m_window, circle, NULL);
}

bool udpateTitleState(State* menuState, sfTime deltaTime)
{
	return true;
}

bool handleTitleStateEvent(State* menuState, const sfEvent* event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyP)
	{
		menuState->requestStackPop(menuState);
		menuState->requestStackPush(menuState, pause);
	}

	return true;
}
