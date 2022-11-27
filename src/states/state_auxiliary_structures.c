#include "state_auxiliary_structures.h"
#include "state_stack.h"

#include <stdlib.h>

PendingChangeArray pendingChangeArrayCreate()
{
	PendingChangeArray pendingChangeArray = { 0, NULL };
	return pendingChangeArray;
}

void pendingChangeArrayDestroy(PendingChangeArray* pendingChangeArray)
{
	free(pendingChangeArray->m_data);
}

void pendingChangeArrayPushBack(PendingChangeArray* pendingChangeArray, PendingChange* change)
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

StateArray stateArrayCreate()
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

	for (int before = 0; before < length; ++before)
	{
		data[before] = stateArray->m_data[before];
	}

	free(stateArray->m_data);
	stateArray->m_data = data;
	--stateArray->m_length;
}

void stateArrayClear(StateArray* stateArray)
{
	free(stateArray->m_data);
	stateArray->m_data = NULL;
	stateArray->m_length = 0;
}
