#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "IPathfinding.h"

class __declspec(dllexport) OnTargetUnreachableTransition: public Transition
{
public:
	OnTargetUnreachableTransition(Detectable *owner, Detectable *target, 
		irr::IrrlichtDevice* device, IPathfinding *pathfinding);
	OnTargetUnreachableTransition(Detectable *owner, Detectable *target, 
		irr::IrrlichtDevice* device, IPathfinding *pathfinding, State* state);
	OnTargetUnreachableTransition(Detectable *owner, Detectable *target, 
		irr::f32 timeout, irr::f32 deviation, irr::IrrlichtDevice* device, IPathfinding *pathfinding);
	OnTargetUnreachableTransition(Detectable *owner, Detectable *target, 
		irr::f32 timeout, irr::f32 deviation, irr::IrrlichtDevice* device, IPathfinding *pathfinding, State* state);
	~OnTargetUnreachableTransition();

	bool condition();
	void reset();

	void setTarget(Detectable* target);
private:

	void resetTimer();

	Detectable *owner;
	Detectable *target;

	// The distance between the current position and the target that is still ok
	irr::f32 deviation;

	// How long state owner should wait until the point is unreachable
	irr::f32 timeout;

	// Saves the last known position of the owner
	// If this position won't change after some time, the position is most probably unreachable and
	// the condition will return true
	irr::core::vector3df lastPosition;

	// Timer variables
	irr::u32 now;
	irr::u32 then;
	irr::f32 frameDeltaTime;
	irr::f32 timer;

	// Irrlicht device
	irr::IrrlichtDevice* device;

	// Pathfinding
	IPathfinding *pathfinding;
};

