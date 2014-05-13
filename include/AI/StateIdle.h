#include "ai/State.h"
#include <functional>

#pragma once
/**
 * StateIdle
 * Classic idle state for NPCs
 */
class __declspec(dllexport) StateIdle : public State
{
public:
	StateIdle(std::function<void(void*)> callbackFunction, void* callbackParameter);
	~StateIdle(void);

	/** Inherited Methods **/
	void enter();
	void exit();
private:
	std::function<void(void*)> callbackFunction;
	void* callbackParameter;

	/** Inherited Methods **/
	void action();
};
