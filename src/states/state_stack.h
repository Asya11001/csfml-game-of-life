#ifndef STATE_STACK_STRUCTURE_H
#define STATE_STACK_STRUCTURE_H

#include "state_identifiers.h"
#include "state.h"

typedef enum Action
{
	push,
	pop,
	clear
} Action;

typedef struct PendingChange
{
	Action action;
	StateId id;
} PendingChange;

typedef struct StateStack
{

} StateStack;

void update(StateStack* stateStack);
void draw(StateStack* stateStack);
void handleEvent(StateStack* stateStack);

void pushState(StateStack* stateStack, StateId id);
void popState(StateStack* stateStack);
void clearState(StateStack* stateStack);

// to avoid changing the state stack during its update or iteration
static void applyPendingChanges(StateStack* stateStack);

#endif