#pragma once

#include <vector>
class State;

/**
 * Transition
 * The transition between two states
 */

class __declspec(dllexport) Transition
{
private:
	/**
	* the owner of the transition
	*/
	State* owner;

	/**
	* the target where the transition should go to
	*/
	State* target;

public:
	virtual ~Transition(void);

	/**
	* Checks if the condition for this transition are fulfilled
	*/
	virtual bool condition(void) = 0;
	
	/**
	* the setter for the owner
	*/
	virtual void setOwner(State* own){owner = own;};

	/**
	* the setter for the target
	*/
	virtual void setTarget(State* tar){target = tar;};
	
	/**
	* the getter for the owner
	*/
	virtual State* getOwner(){return owner;};

	/**
	* the getter for the target
	*/
	virtual State* getTarget(){return target;};
	
	/**
	* the priority of the transition
	*/
	unsigned int priority;

};
