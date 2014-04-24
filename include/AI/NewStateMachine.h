#include "ai/State.h"
#include <algorithm>
#include <vector>

#pragma once

class __declspec(dllexport) NewStateMachine
{
public: 

	NewStateMachine():
		globalState(NULL)
	{}

	NewStateMachine(State* currentState, State* global)
	{
		globalState = global;
		addState(currentState);
		push(currentState);
	}

	virtual ~NewStateMachine(void)
	{}


	/**
	 * Call this method to execute the global and current state.
	 */
	void update() 
	{
		// If a global state exists, call its execute method
		if (globalState != NULL && globalState->executeable())
		{
			push(globalState);
		}else{

			//Checks if there is some executeable states and add them to the stack by priority.
			if(states.size()){
				for(std::vector<int>::size_type i = 0; i < states.size(); i++) {
					if(states[i]->executeable())
						push(states[i]);
				}
			}

			//Eliminates the current state if is not executeable anymore.
			if(getCurrentState() && !getCurrentState()->executeable())
				pop();
		}

		//Executes the current state
		if(getCurrentState())
				getCurrentState()->execute();

	}

	/**
	 * Goes back to the previous state
	 */
	void pop(){
		State* aux = getCurrentState();
		aux->exit();
		stack.erase(std::remove(stack.begin(), stack.end(), aux), stack.end());
		if(stack.size())
			getCurrentState()->enter();
	}

	/**
	 * Sets the new current state
	 */
	void push(State* s){

		if(stack.size()){
			for(std::vector<int>::size_type i = 0; i < stack.size(); i++) {
				if(stack[i] == s)
					return;
			}
			getCurrentState()->exit();
		}

		stack.push_back(s);
		getCurrentState()->enter();
	}

	/**
	 * Sets the global state
	 */
	void setGlobalState(State* s)
	{
		globalState = s;
	}

	/**
	 * Gets the current state
	 */
	State* getCurrentState()
	{
		if(!stack.size())
			return NULL;

		return stack[stack.size()-1];
	}

	/**
	* Adds a new state
	*/
	void addState(State* state)
	{
		states.push_back(state);
		sort();
	}

	/**
	* Removes the state from the list
	*/
	void removeState(State* state)
	{
		states.erase(std::remove(states.begin(), states.end(), state));
	}

	/**
	* Sorts the states list by priority
	*/
	void sort()
	{
		std::sort(states.begin(), states.end(), compare);
	}

	/**
	* Comparator for the states
	*/
	bool static compare(State* state1, State* state2)
	{
		return state1->priority > state2->priority;
	}

	State* globalState;
	std::vector<State*> stack;
	std::vector<State*> states;

protected:
	
};
