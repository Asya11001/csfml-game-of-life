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

	// virtual destructor:
	state->deleteState = deleteMenuState;

	return state;
}

void deleteMenuState(State* state)
{
	// derived destructor:
	MenuState* derivedPart = (MenuState*)state->m_derived;
	free(derivedPart);
	// base destructor:
	deleteState(state);
}

void drawMenuState(State* menuState)
{
	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, 100.0f);
	sfCircleShape_setFillColor(circle, sfGreen);
	Context context = getContext(menuState);
	sfRenderWindow_drawCircleShape(context.m_window, circle, NULL);
	sfCircleShape_destroy(circle);
}

bool updateMenuState(__attribute__((unused)) State* menuState,
		__attribute__((unused)) sfTime deltaTime)
{
	return true;
}

bool handleMenuStateEvent(State* menuState, const sfEvent* event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyP)
	{
		menuState->requestStackPop(menuState);
		menuState->requestStackPush(menuState, pause);
	}
	else if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
	{
		menuState->requestStackClear(menuState);
	}

	return true;
}
