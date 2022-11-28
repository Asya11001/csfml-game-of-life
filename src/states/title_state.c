#include "title_state.h"

#include <stdlib.h>

State* createTitleState(StateStack* stateStack, Context context)
{
	// construct the base class
	State* state = createNewState(stateStack, context);
	// construct the derived class
	TitleState* titleState = malloc(sizeof(TitleState));
	// point to derived object
	state->m_derived = titleState;
	// initialize derived class members
	titleState->draw = drawTitleState;
	titleState->update = udpateTitleState;
	titleState->handleEvent = handleTitleStateEvent;

	// todo: virtual destructor
	return state;
}

void drawTitleState(TitleState* titleState)
{

}

bool udpateTitleState(TitleState* titleState, sfTime deltaTime)
{
	return true;
}

bool handleTitleStateEvent(TitleState* titleState, const sfEvent* event)
{
	if (event->type == sfEvtKeyPressed)
	{
		titleState->m_base->requestStackPop(titleState->m_base);
		titleState->m_base->requestStackPush(titleState->m_base, menu);
	}

	return true;
}
