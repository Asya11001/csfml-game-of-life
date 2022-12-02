#ifndef	STATE_STACK_H
#define STATE_STACK_H

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

State* createStateById(StateStack* stateStack, StateId id);

void updateStateStack(StateStack* stateStack, sfTime deltaTime);
void drawStateStack(StateStack* stateStack);
void handleStateStackEvent(StateStack* stateStack, const sfEvent* event);

void pushStateToStack(StateStack* stateStack, StateId id);
void popStateFromStack(StateStack* stateStack);
void clearStateStack(StateStack* stateStack);

bool isStateStackEmpty(StateStack* stateStack);

// to avoid changing the state stack during its update or iteration
void applyPendingChanges(StateStack* stateStack);

#endif
