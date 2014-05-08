#pragma once

#include "AI\Transition.h"

class __declspec(dllexport) OnKnockedDownTransition: public Transition
{
private:
	unsigned int* health;

public:
	OnKnockedDownTransition(unsigned int* hp);
	~OnKnockedDownTransition();

	bool condition();
};

