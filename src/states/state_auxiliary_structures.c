#include "state_auxiliary_structures.h"
#include "state_stack.h"
#include "title_state.h"
#include "menu_state.h"
#include "pause_state.h"
#include "game_state.h"

#include <assert.h>
#include <stdlib.h>

PendingChangeArray pendingChangeArrayCreate(void)
{
	PendingChangeArray pendingChangeArray = { 0, NULL };
	return pendingChangeArray;
}

void pendingChangeArrayDestroy(PendingChangeArray* pendingChangeArray)
{
	free(pendingChangeArray->m_data);
}

void pendingChangeArrayPushBack(PendingChangeArray* pendingChangeArray, const PendingChange* change)
{
	int length = pendingChangeArray->m_length;

	PendingChange* data = malloc((length + 1) * sizeof(PendingChange));

	for (int before = 0; before < length; ++before)
	{
		data[before] = pendingChangeArray->m_data[before];
	}

	data[length] = *change;

	free(pendingChangeArray->m_data);
	pendingChangeArray->m_data = data;
	++pendingChangeArray->m_length;
}

void pendingChangeArrayClear(PendingChangeArray* pendingChangeArray)
{
	free(pendingChangeArray->m_data);
	pendingChangeArray->m_data = NULL;
	pendingChangeArray->m_length = 0;
}

PendingChange pendingChangeArrayGet(const PendingChangeArray* pendingChangeArray, int index)
{
	assert(index >= 0 && index < pendingChangeArray->m_length && "invalid index pendingChangeArr\n");

	return pendingChangeArray->m_data[index];
}

StateArray stateArrayCreate(void)
{
	StateArray stateArray = { 0, NULL };
	return stateArray;
}

void stateArrayDestroy(StateArray* stateArray)
{
	free(stateArray->m_data);
}

void stateArrayPushBack(StateArray* stateArray, State* state)
{
	int length = stateArray->m_length;
	// create new array one element larger than the old one
	State** data = malloc((length + 1) * sizeof(State*));

	// copy all elements up to the end
	for (int before = 0; before < length; ++before)
	{
		data[before] = stateArray->m_data[before];
	}

	data[length] = state;

	// free all of the state memory:
	for (int i = 0; i < length; ++i)
	{
		stateArray->m_data[i]->deleteState(stateArray->m_data[i]);
	}

	free(stateArray->m_data);
	stateArray->m_data = data;
	++stateArray->m_length;
}

void stateArrayPopBack(StateArray* stateArray)
{
	int length = stateArray->m_length;

	if (length == 1)
	{
		stateArrayClear(stateArray);
		return;
	}

	State** data = malloc((length - 1) * sizeof(State*));

	for (int before = 0; before < length - 1; ++before)
	{
		data[before] = stateArray->m_data[before];
	}

	// free the state memory that the array points to:
	for (int i = 0; i < length; ++i)
	{
		stateArray->m_data[i]->deleteState(stateArray->m_data[i]);
	}

	free(stateArray->m_data);
	stateArray->m_data = data;
	--stateArray->m_length;
}

void stateArrayClear(StateArray* stateArray)
{
	stateArray->m_data[0]->deleteState(stateArray->m_data[0]);

	free(stateArray->m_data);
	stateArray->m_data = NULL;
	stateArray->m_length = 0;
}

State* stateArrayGet(StateArray* stateArray, int index)
{
	assert(index >= 0 && index < stateArray->m_length && "invalid index stateArray\n");

	return stateArray->m_data[index];
}
