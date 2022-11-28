#include "pause_state.h"

#include <SFML/Graphics/CircleShape.h>

#include <stdlib.h>

State* createPauseState(StateStack* stateStack, Context context)
{
	// construct base class
	State* state = createNewState(stateStack, context);
	// construct the derived class
	PauseState* pauseState = malloc(sizeof(PauseState));

	state->m_derived = pauseState;

	// virtual functions:
	state->draw = drawPauseState;
	state->update = updatePauseState;
	state->handleEvent = handlePauseStateEvent;

	return state;
}

void drawPauseState(State* pauseState)
{
	sfCircleShape* circle = sfCircleShape_create();
	sfCircleShape_setRadius(circle, 100.0f);
	sfCircleShape_setFillColor(circle, sfRed);
	Context context = getContext(pauseState);
	sfRenderWindow_drawCircleShape(context.m_window, circle, NULL);
}

bool updatePauseState(State* pauseState, sfTime deltaTime)
{
	return true;
}

bool handlePauseStateEvent(State* pauseState, const sfEvent* event)
{
	if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape)
	{
		pauseState->requestStackPop(pauseState);
		pauseState->requestStackPush(pauseState, game);
	}

	return true;
}
