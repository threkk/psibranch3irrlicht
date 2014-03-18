#include "StateFollowRoute.h"


StateFollowRoute::StateFollowRoute(Detectable* stateOwner, std::vector<irr::core::vector3df>* route, IPathfinding* pathUtil, std::function<void(irr::core::vector3df)> callbackFunction)
{
	this->owner = stateOwner;
	this->route = *route;
	this->pathUtil = pathUtil;

	this->callbackFunction = callbackFunction;
}

StateFollowRoute::~StateFollowRoute(void)
{
}

bool StateFollowRoute::executeable(void)
{
	return true;
}

void StateFollowRoute::action()
{
	// Get a path from the state owner's position to the first point in the route
	std::vector<irr::core::vector3df> path = pathUtil->returnPath(&this->owner->getPosition(), &this->route.front());

	// If there is a path to the next point
	if (!path.empty() && path.size() > 1)
	{
		// Move to it
		if (this->owner->getPosition().getDistanceFrom(path.at(1)) > 100)
		{
			// Call callback method
			callbackFunction(path.at(1));
		}
		// If the point is reached
		else
		{
			// Rotate the route vector to put the next point first in line
			std::rotate(route.begin(), route.begin() + 1, route.end());
		}
	}
}
