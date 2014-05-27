#include "ai\OnPositionUnreachableTransition.h"

OnPositionUnreachableTransition::OnPositionUnreachableTransition(Detectable *owner, irr::core::vector3df position,
	irr::IrrlichtDevice* device, IPathfinding *pathfinding)
	: owner(owner), position(position), timeout(10), deviation(100), device(device), pathfinding(pathfinding), Transition()
{
}

OnPositionUnreachableTransition::OnPositionUnreachableTransition(Detectable *owner, irr::core::vector3df position,
	irr::IrrlichtDevice* device, IPathfinding *pathfinding, State* state)
	: owner(owner), position(position), timeout(10), deviation(100), device(device), pathfinding(pathfinding), Transition(state)
{
}

OnPositionUnreachableTransition::OnPositionUnreachableTransition(Detectable *owner, irr::core::vector3df position,
	irr::f32 timeout, irr::f32 deviation, irr::IrrlichtDevice* device, IPathfinding *pathfinding)
	: owner(owner), position(position), timeout(timeout), deviation(deviation), device(device), pathfinding(pathfinding), Transition()
{
}

OnPositionUnreachableTransition::OnPositionUnreachableTransition(Detectable *owner, irr::core::vector3df position,
	irr::f32 timeout, irr::f32 deviation, irr::IrrlichtDevice* device, IPathfinding *pathfinding, State* state)
	: owner(owner), position(position), timeout(timeout), deviation(deviation), device(device), pathfinding(pathfinding), Transition(state)
{
}

OnPositionUnreachableTransition::~OnPositionUnreachableTransition()
{
}

void OnPositionUnreachableTransition::setPosition(irr::core::vector3df position)
{
	this->position = position;
}

bool OnPositionUnreachableTransition::condition()
{
	// Update timer
	now = device->getTimer()->getTime();
	frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;

	// If owner is at point
	if (owner->getPosition().getDistanceFrom(position) > deviation)
	{
		std::vector<irr::core::vector3df> path;
		if ( !pathfinding->returnPath(&owner->getPosition(), &position, &path) || path.empty())
		{
			// If there is no path
			return true;
		} else if ( owner->getPosition().getDistanceFrom(lastPosition) <= deviation )
		{
			// If point has not changed since last time
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

void OnPositionUnreachableTransition::reset()
{
	resetTimer();
}

void OnPositionUnreachableTransition::resetTimer()
{
	// Reset timer variables
	now = then = device->getTimer()->getTime();
	timer = 0;
}