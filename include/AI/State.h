#pragma once

#include <vector>

class __declspec(dllexport) State
{
public:
	virtual ~State(void);

	/**
	 * Will be called when this state is entered
	 */
	virtual void enter() = 0;

	/**
	 * Will be called when this state is exited
	 */
	virtual void exit() = 0;

	/**
	* Subsumption: Checks if the requirements for this state are fulfilled
	*/
	virtual bool executeable(void) = 0;

	/**
	* Executes one of the substates or this state
	*/
	void execute(void);

	/**
	* Subsumption: Adds a new substate
	*/
	void addSubState(State* state);

	/**
	* Subsumption: Removes the substate from the list
	*/
	void removeSubState(State* state);

	// Subsumption: If more than one state can be executed, the state with the highest priority will be executed
	int priority;
	 
private:
	// Contains substates in a sorted vector (highest first)
	std::vector<State*> substates;

	/**
	* Sort the vector
	*/
	void sort();

	/**
	* State-Priority-Comparator Method
	*/
	bool static State::compare(State* state1, State* state2);

protected:
	/**
	* This is the real method, that defines what the NPC is doing. <br/>
	* This method will be called by execute.
	*/
	virtual void action() = 0;

	/**
	* This function will run if the state is not executable <br/>
	* This method will be called by execute.
	* This function doesn't do anything and needs to be overriden by the other states.
	*/
	virtual void noActionFallback();
};
