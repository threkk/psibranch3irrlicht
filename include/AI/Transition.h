#pragma once

#include <vector>
#include <functional>

class State;

/**
 * Transition
 * The transition between two states
 */

class __declspec(dllexport) Transition
{
protected:
	/**
	* the owner of the transition
	*/
	State* ownerState;

	/**
	* the target where the transition should go to
	*/
	State* targetState;

public:
	Transition() : callbackOnConditionTrue(NULL), callbackParameter(NULL) {}
	Transition(State *target) : callbackOnConditionTrue(NULL), callbackParameter(NULL), targetState(target) {}

	virtual ~Transition(void) {}

	/**
	* Checks if the condition for this transition are fulfilled
	*/
	virtual bool condition(void) = 0;

	/**
	 * Reset the transition
	 */
	virtual void reset(void) {};
	
	/**
	* the setter for the owner
	*/
	virtual void setOwner(State* own){ownerState = own;};

	/**
	* the setter for the target
	*/
	virtual void setTarget(State* tar){targetState = tar;};
	
	/**
	* the getter for the owner
	*/
	virtual State* getOwner(){return ownerState;};

	/**
	* the getter for the target
	*/
	virtual State* getTarget(){return targetState;};
	
	/**
	* the priority of the transition
	*/
	unsigned int priority;

	/**
	 * If set, this function will be called
	 * if the condition is true and the state will be changed
	 */
	std::function<void (void*)> callbackOnConditionTrue;

	/**
	 * Callback Parameters
	 */
	void* callbackParameter;
};
