#include "ai/State.h"
#include <algorithm>

#include "AI/StateMachine.h"

State::~State(void)
{
	// Delete the substates
	if ( !transitions.empty() )
	{
		for ( size_t i = 0; i < transitions.size(); i++ )
		{
			delete transitions[i];
		}
	}
}

void State::execute(void) 
{
		
	for ( unsigned int j = 0; j < transitions.size(); j++ )
	{
		if ( transitions[j]->condition())
		{
			stateMachine->changeState(transitions[j]->getTarget());
			return;
		}
	}

	// No executable substate? Execute this state
	action();
}

void State::addTransition(Transition* transition)
{
	transitions.push_back(transition);
	sort();
}

void State::removeTransition(Transition* transition)
{
	transitions.erase(std::remove(transitions.begin(), transitions.end(), transition));
}

void State::sort()
{
	std::sort(transitions.begin(), transitions.end(), compare);
}

bool State::compare(Transition* transition1, Transition* transition2)
{
	return transition1->priority > transition2->priority;
}