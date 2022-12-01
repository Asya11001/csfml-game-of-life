#include "state_stack.h"
#include "title_state.h"
#include "menu_state.h"
#include "pause_state.h"
#include "game_state.h"

#include <stdlib.h>

StateStack createStateStack(Context context)
{
	StateStack stateStack = { {}, {}, context };
	return stateStack;
}

State* createStateById(StateStack* stateStack, StateId id)
{
	switch (id)
	{
		case title:
		{
			State* titleState = createTitleState(stateStack, stateStack->m_context);
			return titleState;
		}
		case menu:
		{
			State* menuState = createMenuState(stateStack, stateStack->m_context);
			return menuState;
		}
		case pause:
		{
			State* pauseState = createPauseState(stateStack, stateStack->m_context);
			return pauseState;
		}
		case game:
		{
			State* gameState = createGameState(stateStack, stateStack->m_context);
			return gameState;
		}
		default:
			return createNewState(stateStack, stateStack->m_context);
	}
}

void updateStateStack(StateStack* stateStack, sfTime deltaTime)
{
	// update from highest state to lowest
	int lastStateIndex = stateStack->m_stack.m_length - 1;
	for (int i = lastStateIndex; i >= 0; --i)
	{
		State* state = stateArrayGet(&stateStack->m_stack, i);
		if (!state->update(state, deltaTime))
			return;
	}

	applyPendingChanges(stateStack);
}

void drawStateStack(StateStack* stateStack)
{
	// the first state to be drawn is the oldest (lowest) one
	for (int i = 0; i < stateStack->m_stack.m_length; ++i)
	{
		State* state = stateArrayGet(&stateStack->m_stack, i);
		state->draw(state);
	}
}

void handleStateStackEvent(StateStack* stateStack, const sfEvent* event)
{
	int lastStateIndex = stateStack->m_stack.m_length - 1;
	for (int i = lastStateIndex; i >= 0; --i)
	{
		State* state = stateArrayGet(&stateStack->m_stack, i);
		if (!state->handleEvent(state, event))
			return;
	}

	applyPendingChanges(stateStack);
}

void pushStateToStack(StateStack* stateStack, StateId id)
{
	PendingChange change = createPendingChange(push, id);
	pendingChangeArrayPushBack(&stateStack->m_pendingList, &change);
}

void popStateFromStack(StateStack* stateStack)
{
	PendingChange change = createPendingChangeDefaultStateId(pop);
	pendingChangeArrayPushBack(&stateStack->m_pendingList, &change);
}

void clearStateStack(StateStack* stateStack)
{
	PendingChange change = createPendingChangeDefaultStateId(clear);
	pendingChangeArrayPushBack(&stateStack->m_pendingList, &change);
}

bool isStateStackEmpty(StateStack* stateStack)
{
	return (stateStack->m_stack.m_length == 0);
}

void applyPendingChanges(StateStack* stateStack)
{
	int numberOfChanges = stateStack->m_pendingList.m_length;
	for (int i = 0; i < numberOfChanges; ++i)
	{
		PendingChange change = pendingChangeArrayGet(&stateStack->m_pendingList, i);
		switch (change.action)
		{
			case push:
			{
				stateArrayPushBack(&stateStack->m_stack, createStateById(stateStack, change.id));
				break;
			}
			case pop:
			{
				stateArrayPopBack(&stateStack->m_stack);
				break;
			}
			case clear:
			{
				stateArrayClear(&stateStack->m_stack);
				break;
			}
		}
	}

	pendingChangeArrayClear(&stateStack->m_pendingList);
}

PendingChange createPendingChange(Action action, StateId id)
{
	PendingChange pendingChange = { action, id };
	return pendingChange;
}

PendingChange createPendingChangeDefaultStateId(Action action)
{
	PendingChange pendingChange = { action, none };
	return pendingChange;
}
