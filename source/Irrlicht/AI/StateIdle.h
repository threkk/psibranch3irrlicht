#include "State.h"
#include <functional>

#pragma once
class StateIdle : public State
{
public:
	StateIdle(std::function<void(void*)> callbackFunction, void* callbackParameter);
	~StateIdle(void);

	/** Inherited Methods **/
	bool executeable(void);
private:
	// The callback function for the idle state
	std::function<void(void*)> callbackFunction;

	// The callback parameters that will be forwarded to the callback function
	void* callbackParameter;

	/** Inherited Methods **/
	void action();
		
};
