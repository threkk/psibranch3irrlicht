#pragma once

#include "ai\Transition.h"

class __declspec(dllexport) OnKnockedDownTransition: public Transition
{
private:
	int* health;

public:
	OnKnockedDownTransition(int* hp);
	OnKnockedDownTransition(int* hp, State* target);
	~OnKnockedDownTransition();

	bool condition();

	void setHealth(int* hp);
};

