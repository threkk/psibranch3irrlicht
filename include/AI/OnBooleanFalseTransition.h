#pragma once

#include "ai\Transition.h"

class __declspec(dllexport) OnBooleanFalseTransition: public Transition
{
public:
	OnBooleanFalseTransition(bool *boolean);
	OnBooleanFalseTransition(bool *boolean, State* state);
	~OnBooleanFalseTransition();

	bool condition();

private:
	bool *boolean;
};

