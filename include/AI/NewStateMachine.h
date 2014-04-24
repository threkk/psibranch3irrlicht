#include "ai/State.h"
#include <algorithm>

#pragma once

class __declspec(dllexport) NewStateMachine
{
public: 

	NewStateMachine():
		globalState(NULL)
	{}

	NewStateMachine(State* currentState, State* globalState):
		globalState(globalState)
	{
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
		if (globalState->executeable()) 
			push(globalState);
		else{

			//Checks if there is some executeable states and add them to the stack by priority.
			if(states.size()){
				for(std::vector<int>::size_type i = 0; i < states.size(); i++) {
					if(states[i]->executeable())
						push(states[i]);
				}
			}

			//Eliminates the current state if is not executeable anymore.
			if(stack.size() && !stack[stack.size()-1]->executeable())
				pop();
			else
				stack[stack.size()-1]->execute(); //Executes the current state
		}	

	}

	/**
	 * Goes back to the previous state
	 */
	void pop(){
		State* aux = stack[stack.size()-1];
		stack.erase(std::remove(stack.begin(), stack.end(), aux), stack.end());
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
		}

		stack.push_back(s);
	}

	/**
	 * Sets the global state
	 */
	void setGlobalState(State* s)
	{
		globalState = s;
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
	bool compare(State* state1, State* state2)
	{
		return state1->priority > state2->priority;
	}

protected:
	State* globalState;
	std::vector<State*> stack;
	std::vector<State*> states;
};
