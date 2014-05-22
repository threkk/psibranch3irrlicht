#include "ai/State.h"
#include <algorithm>

#include "AI/StateMachine.h"

State::State()
{
	// Create the internal statemachine and set the current state to this state
	internalStateMachine = new StateMachine();
	internalStateMachine->setCurrentState(this);
}

State::~State(void)
{
	// Delete internal state machine
	delete internalStateMachine;

	// Delete the transitions
	if ( !transitions.empty() )
	{
		for ( size_t i = 0; i < transitions.size(); i++ )
		{
			delete transitions[i];
		}
	}

	// Delete the transitions to substates
	if ( !internalTransitions.empty() )
	{
		for ( size_t i = 0; i < internalTransitions.size(); i++ )
		{
			delete internalTransitions[i];
		}
	}
}

void State::execute(void) 
{
	// External transition check
	for ( size_t j = 0; j < transitions.size(); j++ )
	{
		if ( transitions[j]->condition())
		{
			if ( stateMachine != NULL )
			{
				// First, call the callback method of the transition if set
				if ( transitions[j]->callbackOnConditionTrue != NULL )
				{
					transitions[j]->callbackOnConditionTrue(transitions[j]->callbackParameter);
				}

				// If no target, return to previous state
				if ( transitions[j]->getTarget() == NULL ) 
				{
					stateMachine->returnToPreviousState();
				} else {
					stateMachine->changeState(transitions[j]->getTarget());
				}
				transitions[j]->reset();
				stateMachine->updateCurrentState();
				return;
			} else {
				printf("WARNING: State machine not set\n");
			}
		}
	}

	// Internal transition check (Substates)
	// Do only if the current state is this state - otherwise we don't look at internal states!
	if ( internalStateMachine->isCurrentState(this) )
	{
		for ( size_t i = 0; i < internalTransitions.size(); i++ )
		{
			if ( internalTransitions[i]->condition())
			{
				// First, call the callback method of the transition if set
				if ( internalTransitions[i]->callbackOnConditionTrue != NULL )
				{
					internalTransitions[i]->callbackOnConditionTrue(transitions[i]->callbackParameter);
				}

				// If no target, return to previous state
				if ( internalTransitions[i]->getTarget() == NULL ) 
				{
					internalStateMachine->returnToPreviousState();
				} else {
					internalStateMachine->changeState(internalTransitions[i]->getTarget());
				}
				internalTransitions[i]->reset();
			}
		}
		// Is this state still the current state?
		if ( internalStateMachine->isCurrentState(this) )
		{
			// Call action
			action();
			return;
		}
	}
	// If we the internal state is not the current state update the internal statemachine
	internalStateMachine->update();
}

void State::addTransition(Transition* transition)
{
	transitions.push_back(transition);
	sort(&transitions);
}

void State::removeTransition(Transition* transition)
{
	transitions.erase(std::remove(transitions.begin(), transitions.end(), transition));
}

void State::addSubTransition(Transition* transition)
{
	internalTransitions.push_back(transition);
	sort(&internalTransitions);
}

void State::removeSubTransition(Transition* transition)
{
	internalTransitions.erase(std::remove(internalTransitions.begin(), internalTransitions.end(), transition));
}

void State::sort(std::vector<Transition*>* list)
{
	std::sort(list->begin(), list->end(), compare);
}

bool State::compare(Transition* transition1, Transition* transition2)
{
	return transition1->priority > transition2->priority;
}

void State::setStateMachine(StateMachine* stateMachine)
{
	// To prevent the internalStateMachine becoming the externalStateMachine,
	// check if it is the same machine
	if ( stateMachine != this->internalStateMachine )
		this->stateMachine = stateMachine;
}