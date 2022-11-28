#ifndef STATE_STACK_STRUCTURE_H
#define STATE_STACK_STRUCTURE_H

#include <stdbool.h>

#include "state.h"
#include "state_auxiliary_structures.h"
#include "state_identifiers.h"

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

PendingChange createPendingChange(Action action, StateId id);
PendingChange createPendingChangeDefaultStateId(Action action);

typedef struct StateStack
{
	StateArray m_stack;
	PendingChangeArray m_pendingList;
	Context m_context;
} StateStack;

StateStack createStateStack(Context context);

State* createStatePtr(StateStack* stateStack, StateId id);

void update(StateStack* stateStack);
void draw(StateStack* stateStack);
void handleEvent(StateStack* stateStack);

void pushState(StateStack* stateStack, StateId id);
void popState(StateStack* stateStack);
void clearState(StateStack* stateStack);

bool isEmpty(StateStack* stateStack);

// to avoid changing the state stack during its update or iteration
static void applyPendingChanges(StateStack* stateStack);

#endif
