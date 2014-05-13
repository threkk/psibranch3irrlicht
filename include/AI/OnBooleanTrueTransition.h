#pragma once

#include "ai\Transition.h"

class __declspec(dllexport) OnBooleanTrueTransition: public Transition
{
public:
	OnBooleanTrueTransition(bool *boolean);
	OnBooleanTrueTransition(bool *boolean, State* state);
	~OnBooleanTrueTransition();

	bool condition();

private:
	bool *boolean;
};

