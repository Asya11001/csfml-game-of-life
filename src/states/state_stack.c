#include "state_stack.h"
#include "title_state.h"

#include <stdlib.h>

StateStack createStateStack(Context context)
{
	StateStack stateStack = { {}, {}, context };
	return stateStack;
}

State* createStatePtr(StateStack* stateStack, StateId id)
{
	switch (id)
	{
		case title:
		{
			State* titleState = createTitleState(stateStack, stateStack->m_context);
			return titleState;
		}
		case menu:
			break;
		case pause:
			break;
		case game:
			break;
		default:
			break;
	}
}

void update(StateStack* stateStack)
{

}

void draw(StateStack* stateStack)
{

}

void handleEvent(StateStack* stateStack)
{

}

void pushState(StateStack* stateStack, StateId id)
{

}

void popState(StateStack* stateStack)
{

}

void clearState(StateStack* stateStack)
{

}

bool isEmpty(StateStack* stateStack)
{
	return (stateStack->m_stack.m_length == 0);
}

static void applyPendingChanges(StateStack* stateStack)
{
	int numberOfChanges = stateStack->m_pendingList.m_length;
	for (int i = 0; i < numberOfChanges; ++i)
	{
		PendingChange change = pendingChangeArrayGet(&stateStack->m_pendingList, i);
		switch (change.action)
		{
			case push:
			{
				stateArrayPushBack(&stateStack->m_stack, createStatePtr(stateStack, change.id));
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
