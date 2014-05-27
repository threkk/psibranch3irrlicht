#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"

class __declspec(dllexport) OnPositionNotReachedTransition: public Transition
{
public:
	
	OnPositionNotReachedTransition(Detectable *owner, irr::core::vector3df position);
	OnPositionNotReachedTransition(Detectable *owner, irr::core::vector3df position, State* state);
	OnPositionNotReachedTransition(Detectable *owner, irr::core::vector3df position, irr::f32 deviation);
	OnPositionNotReachedTransition(Detectable *owner, irr::core::vector3df position, irr::f32 deviation, State* state);
	~OnPositionNotReachedTransition();

	bool condition();

private:
	Detectable *owner;
	irr::core::vector3df position;

	// The distance between the current position and the target position that is still ok
	irr::f32 deviation;
};

