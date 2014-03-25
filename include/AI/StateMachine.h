#include "ai/State.h"

#pragma once
class __declspec(dllexport) StateMachine
{
public: 

	StateMachine():
		currentState(NULL),
		previousState(NULL),
		globalState(NULL)
	{}

	StateMachine(State* currentState, State* previousState, State* globalState):
		currentState(currentState),
		previousState(previousState),
		globalState(globalState)
	{}

	virtual ~StateMachine(void)
	{
	}

	// Use these methods to initialize the FSM
	void setCurrentState(State* s)
	{
		currentState = s;
	}
	
	void setGlobalState(State* s)
	{
		globalState = s;
	}
	
	void setPreviousState(State* s)
	{
		previousState = s;
	}

	void changeState(State* state)
	{
		previousState = currentState;
		currentState = state;

		// Exit previous state
		if ( previousState ) previousState->exit();
		// Enter current state
		if ( currentState ) currentState->enter();
	}

	/**
	 * Call this method to update the infinite state machine
	 */
	void update() 
	{
		// If a global state exists, call its execute method
		if (globalState) 
			globalState->execute();

		// Same for the current state
		if (currentState) 
			currentState->execute();

	}

	/**
	 * Set the current state to the previous one.
	 * The current state will then be the new previous state.
	 */
	void returnToPreviousState()
	{
		if ( currentState && previousState ) {
			// Swap states
			State* tmp = currentState;
			currentState = previousState;
			previousState = tmp;

			// Exit previous state
			previousState->exit();
			// Enter current state
			currentState->enter();
		}
	}

	/**
	 * Checks if the given state is the current state
	 */
	bool isCurrentState(State* state)
	{
		return currentState == state;
	}

protected:
	State* globalState;
	State* currentState;
	State* previousState;
};

