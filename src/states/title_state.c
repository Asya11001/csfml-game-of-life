#include "title_state.h"

#include <SFML/Graphics/CircleShape.h>

#include <stdlib.h>

State* createTitleState(StateStack* stateStack, Context context)
{
	// construct the base class
	State* state = createNewState(stateStack, context);
	// construct the derived class
	TitleState* titleState = malloc(sizeof(TitleState));
	// point to derived object
	state->m_derived = titleState;

	// accessing derived class functions:
	state->draw = drawTitleState;
	state->update = updateTitleState;
	state->handleEvent = handleTitleStateEvent;

	// virtual destructor:
	state->deleteState = deleteTitleState;

	return state;
}

void deleteTitleState(State* state)
{
	// derived destructor:
	TitleState* derivedPart = (TitleState*)state->m_derived;
	free(derivedPart);
	// base destructor:
	deleteState(state);
}

void drawTitleState(State* titleState)
{
	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, 100.0f);
	sfCircleShape_setFillColor(circle, sfBlue);
	Context context = getContext(titleState);
	sfRenderWindow_drawCircleShape(context.m_window, circle, NULL);
	sfCircleShape_destroy(circle);
}

bool updateTitleState(__attribute__((unused)) State* titleState,
		__attribute__((unused)) sfTime deltaTime)
{
	return true;
}

bool handleTitleStateEvent(State* titleState, const sfEvent* event)
{
	if (event->type == sfEvtKeyPressed)
	{
		titleState->requestStackPop(titleState);
		titleState->requestStackPush(titleState, menu);
	}

	return true;
}
