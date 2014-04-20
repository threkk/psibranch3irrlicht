#include <vector>

#pragma once

class State
{
public:
	virtual ~State(void);

	/**
	* Checks if the requirements for this state are fulfilled
	*/
	virtual bool executeable(void) = 0;

	/**
	* Executes one of the substates or this state
	*/
	void execute(void);

	/**
	* Adds a new substate
	*/
	void addSubState(State* state);

	/**
	* Removes the substate from the list
	*/
	void removeSubState(State* state);

	// If more than one state can be executed, the state with the highest priority will be executed
	int priority;

private:
	// Contains substates in a sorted vector (highest first)
	std::vector<State*> substates;

	/**
	* This is the real method, that defines what the NPC is doing. <br/>
	* This method will be called by execute.
	*/
	virtual void action() = 0;

	/**
	* Sort the vector
	*/
	void sort();

	/**
	* State-Priority-Comparator Method
	* Returns true if the priority of state 1 is heigher than the priority
	* of state 2
	*/
	bool static State::compare(State* state1, State* state2);

};
