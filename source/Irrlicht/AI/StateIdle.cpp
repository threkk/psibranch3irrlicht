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
	return true;
}

void StateIdle::action()
{
	callbackFunction(callbackParameter);
}
