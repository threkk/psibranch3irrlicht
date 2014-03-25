#include "ai/State.h"
#include <algorithm>

State::~State(void)
{
	// Delete the substates
	if ( !substates.empty() )
	{
		for ( size_t i = 0; i < substates.size(); i++ )
		{
			delete substates[i];
		}
	}
}

void State::execute(void) 
{
	if ( executeable() ) {
		// First check for substates
		if ( !substates.empty() )
		{
			for ( size_t i = 0; i < substates.size(); i++ )
			{
				if ( substates[i]->executeable() )
				{
					return substates[i]->execute();
				}
			}
		}

		// No executable substate? Execute this state
		action();
	}
}

void State::addSubState(State* state)
{
	substates.push_back(state);
	sort();
}

void State::removeSubState(State* state)
{
	substates.erase(std::remove(substates.begin(), substates.end(), state));
}

void State::sort()
{
	std::sort(substates.begin(), substates.end(), compare);
}

bool State::compare(State* state1, State* state2)
{
	return state1->priority > state2->priority;
}