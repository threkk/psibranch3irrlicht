#pragma once

#include "ai\Transition.h"

/**
 * Checks if the health is below or equal to zero
 */
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

