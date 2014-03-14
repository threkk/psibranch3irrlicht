#include "StateIdle.h"


StateIdle::StateIdle(std::function<void(void*)> callbackFunction, void* callbackParameter)
{
	this->callbackFunction = callbackFunction;
	this->callbackParameter = callbackParameter;
}

StateIdle::~StateIdle(void)
{
}

bool StateIdle::executeable(void)
{
	// It's always possible to be idle
	return true;
}

void StateIdle::action()
{
	// Call the callback function
	callbackFunction(callbackParameter);
}
