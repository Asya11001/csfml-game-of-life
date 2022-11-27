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
