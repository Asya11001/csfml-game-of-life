#include "state_stack.h"

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

static void applyPendingChanges(StateStack* stateStack)
{

}

PendingChange pendingChangeCreate(Action action, StateId id)
{
	PendingChange pendingChange = { .action = action, .id = id };
	return pendingChange;
}

PendingChange pendingChangeCreateDefaultStateId(Action action)
{
	PendingChange pendingChange = { .action = action, .id = none };
	return pendingChange;
}
