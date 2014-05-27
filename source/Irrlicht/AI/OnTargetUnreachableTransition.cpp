#include "ai\OnTargetUnreachableTransition.h"

OnTargetUnreachableTransition::OnTargetUnreachableTransition(Detectable *owner, Detectable *target,
	irr::IrrlichtDevice* device, IPathfinding *pathfinding)
	: owner(owner), target(target), timeout(3), deviation(100), device(device), pathfinding(pathfinding), Transition()
{
}

OnTargetUnreachableTransition::OnTargetUnreachableTransition(Detectable *owner,  Detectable *target,
	irr::IrrlichtDevice* device, IPathfinding *pathfinding, State* state)
	: owner(owner), target(target), timeout(3), deviation(100), device(device), pathfinding(pathfinding), Transition(state)
{
}

OnTargetUnreachableTransition::OnTargetUnreachableTransition(Detectable *owner, Detectable *target,
	irr::f32 timeout, irr::f32 deviation, irr::IrrlichtDevice* device, IPathfinding *pathfinding)
	: owner(owner), target(target), timeout(timeout), deviation(deviation), device(device), pathfinding(pathfinding), Transition()
{
}

OnTargetUnreachableTransition::OnTargetUnreachableTransition(Detectable *owner, Detectable *target,
	irr::f32 timeout, irr::f32 deviation, irr::IrrlichtDevice* device, IPathfinding *pathfinding, State* state)
	: owner(owner), target(target), timeout(timeout), deviation(deviation), device(device), pathfinding(pathfinding), Transition(state)
{
}

OnTargetUnreachableTransition::~OnTargetUnreachableTransition()
{
}

void OnTargetUnreachableTransition::setTarget(Detectable *target)
{
	this->target = target;
}

bool OnTargetUnreachableTransition::condition()
{
	if ( target == NULL ) return false;

	// Update timer
	now = device->getTimer()->getTime();
	frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;

	// If owner is not at the same position as the target
	if (owner->getPosition().getDistanceFrom(target->getPosition()) > deviation)
	{
		// If there is no path OR
		// if point has not changed since last time
		std::vector<irr::core::vector3df> path;
		if ( !pathfinding->returnPath(&owner->getPosition(), &target->getPosition(), &path) ||
			path.empty() ||
			owner->getPosition().getDistanceFrom(lastPosition) <= deviation )
		{
			
			// Increase the timer
			timer += frameDeltaTime;

			// Timeout?
			if (timer >= timeout)
			{
				return true;
			}
		} else {
			resetTimer();
		}
	}
	// Point is reached
	return false;
}

void OnTargetUnreachableTransition::reset()
{
	resetTimer();
}

void OnTargetUnreachableTransition::resetTimer()
{
	// Reset timer variables
	now = then = device->getTimer()->getTime();
	timer = 0;
}