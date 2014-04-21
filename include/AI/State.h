#pragma once

#include <vector>

/**
 * State
 * The state that is used for AI Behavior.
 * There are two different ways to use the states. Either with the finite state machine
 * and/or as states in a subsumption architecture.
 *
 * Finite state machine:
 * By using the finite state machine each NPC will have one state machine, that controlls the states for the NPC.
 * By activating an different state it will automatically call the exit() method of the current state
 * and the enter() method of the new state. After that each the execute() method will be called each update.
 * To change a state add your transitions to the action() method.
 * 
 * Subsumption architecture:
 * By using the subsumption architecture you will have a priority list of different states.
 * The first executable() state will be the "active" state and supresses all action()-methods of other states.
 * Because each update the requirements of other states can be fulfilled, it will never call any enter() or exit() methods.
 * The subsumption architecture is fast but not as flexible as the finite state machine.
 *
 * It is possible to combine both patterns if wanted.
 * 
 * Note: We will change the finite state machine to an hierarchical finite state machine, that also supports substates as the 
 * subsumption architecture. Maybe the subsumption architecture will be removed after the new state works.
 */
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
	* This is the real method, that defines what the NPC is doing
	* This method will be called by execute.
	*/
	virtual void action() = 0;

	/**
	* This function will run if the state is not executable
	* This method will be called by execute.
	* This function doesn't do anything and needs to be overwridden by the other states.
	*/
	virtual void noActionFallback();
};
