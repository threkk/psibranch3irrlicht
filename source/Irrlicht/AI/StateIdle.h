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
	std::function<void(void*)> callbackFunction;
	void* callbackParameter;

	/** Inherited Methods **/
	void action();
		
};
