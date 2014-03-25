#include "ai/State.h"
#include <functional>

#pragma once
class __declspec(dllexport) StateIdle : public State
{
public:
	StateIdle(std::function<void(void*)> callbackFunction, void* callbackParameter);
	~StateIdle(void);

	/** Inherited Methods **/
	bool executeable(void);
	void enter();
	void exit();
private:
	std::function<void(void*)> callbackFunction;
	void* callbackParameter;

	/** Inherited Methods **/
	void action();
};
