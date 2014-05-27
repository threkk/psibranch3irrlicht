#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"

class __declspec(dllexport) OnPositionReachedTransition: public Transition
{
public:
	
	OnPositionReachedTransition(Detectable *owner, irr::core::vector3df position);
	OnPositionReachedTransition(Detectable *owner, irr::core::vector3df position, State* state);
	OnPositionReachedTransition(Detectable *owner, irr::core::vector3df position, irr::f32 deviation);
	OnPositionReachedTransition(Detectable *owner, irr::core::vector3df position, irr::f32 deviation, State* state);
	~OnPositionReachedTransition();

	bool condition();

private:
	Detectable *owner;
	irr::core::vector3df position;

	// The distance between the current position and the target position that is still ok
	irr::f32 deviation;
};

