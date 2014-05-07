#include "ai/State.h"
#include <algorithm>
#include <vector>

#pragma once
/**
 * StateMachine
 * By using the finite state machine each NPC will have one state machine, that controlls the states for the NPC.
 * By activating an different state it will automatically call the exit() method of the current state
 * and the enter() method of the new state. After that each the execute() method will be called each update.
 * To change a state add your transitions to the action() method.
 * 
 * The NPC should call the update() method each round.
 * During the update() the global state and the current state will be executed.
 * Changing the state will be part of the action() method of the current active state, as it will call the 
 * changeState() method or the returnToPreviousState() method.
 * Ensure that all your transitions are implemented (only) in the states.
 *
 * The state machine supports two different states:
 *   - Global State
 *     If set, this state will be executed before the normal state, independent from the current state.
 *   - Current State
 *     This is the state the NPC will be usually executed. By changing states, only the current state will be affected.
 */
class __declspec(dllexport) StateMachine
{
public: 

	std::vector<State*> stack;

	StateMachine():
		currentState(NULL),
		globalState(NULL)
	{}

	StateMachine(State* currentState, State* previousState, State* globalState):
		currentState(currentState),
		globalState(globalState)
	{
		setPreviousState(previousState);
	}

	virtual ~StateMachine(void)
	{
	}

	/** Use these methods to initialize the FSM **/

	/**
	 * Returns the previous state and eliminates it of the stack
	 */
	State* pop(){
		State* res = NULL;

		if(stack.size())
		{
			res = stack[stack.size()-1];
			stack.erase(std::remove(stack.begin(), stack.end(), res), stack.end());
		}

		return res;
	}

	/**
	 * Pushes a state to the stack
	 */
	void push(State* s){
		stack.push_back(s);
	}

	/**
	 * Sets the current state
	 */
	void setCurrentState(State* s)
	{
		currentState = s;
	}

	/**
	 * Gets the previous state
	 */
	State* getPreviousState()
	{
		if(!stack.size())
			return NULL;

		return stack[stack.size()-1];
	}
	
	/**
	 * Sets the global state
	 */
	void setGlobalState(State* s)
	{
		globalState = s;
	}
	
	/**
	 * Sets the previous state
	 */
	void setPreviousState(State* s)
	{
		push(s);
	}

	/** Use these methods to use the FSM **/

	/**
	 * Change the current state.
	 * The exit() method of the current state will be called and
	 * the enter() method of the new state will be called within this method.
	 */
	void changeState(State* state)
	{

		if ( currentState )
		{
			currentState->exit();
			setPreviousState(currentState);
		}

		currentState = state;
		if ( currentState ) currentState->enter();
		
	}

	/**
	 * Call this method to execute the global and current state.
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
		if ( currentState && stack.size() ) {

			currentState->exit();
			currentState = pop();
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
};

