#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "IPathfinding.h"

/**
 * Checks if the position is not reachable.
 */
class __declspec(dllexport) OnPositionUnreachableTransition: public Transition
{
public:
	OnPositionUnreachableTransition(Detectable *owner, irr::core::vector3df position, 
		irr::IrrlichtDevice* device, IPathfinding *pathfinding);
	OnPositionUnreachableTransition(Detectable *owner, irr::core::vector3df position, 
		irr::IrrlichtDevice* device, IPathfinding *pathfinding, State* state);
	OnPositionUnreachableTransition(Detectable *owner, irr::core::vector3df position, 
		irr::f32 timeout, irr::f32 deviation, irr::IrrlichtDevice* device, IPathfinding *pathfinding);
	OnPositionUnreachableTransition(Detectable *owner, irr::core::vector3df position, 
		irr::f32 timeout, irr::f32 deviation, irr::IrrlichtDevice* device, IPathfinding *pathfinding, State* state);
	~OnPositionUnreachableTransition();

	bool condition();
	void reset();

	void setPosition(irr::core::vector3df position);
private:

	void resetTimer();

	Detectable *owner;
	irr::core::vector3df position;

	// The distance between the current position and the target position that is still ok
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

