#pragma once

#include "AI\Transition.h"

class __declspec(dllexport) OnSpotTransition: public Transition
{
public:
	OnSpotTransition();
	~OnSpotTransition();

	bool condition();
};

