#include "state_auxiliary_structures.h"

#include <stdlib.h>

StateArray stateArray_create()
{
	StateArray stateArray;
	stateArray.m_length = 0;

	return stateArray;
}

void stateArray_push_back(StateArray* stateArray, State* state)
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

void stateArray_pop_back(StateArray* stateArray)
{
	int length = stateArray->m_length;

	if (length == 1)
	{
		stateArray_clear(stateArray);
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

void stateArray_clear(StateArray* stateArray)
{

}
