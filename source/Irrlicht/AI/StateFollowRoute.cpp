#include "ai/StateFollowRoute.h"


StateFollowRoute::StateFollowRoute(Detectable* stateOwner, std::vector<std::pair<irr::core::vector3df, float>>* route, float offset, IrrlichtDevice* device,
	IPathfinding* pathUtil, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction)
{
	this->stateOwner = stateOwner;
	this->route = *route;
	this->device = device;
	this->pathUtil = pathUtil;

	this->offset = offset;
	this->pointToVisit = 0;
	this->timer = 0;
	this->then = this->device->getTimer()->getTime();

	this->callbackFunction = callbackFunction;
}

StateFollowRoute::~StateFollowRoute(void)
{
}

bool StateFollowRoute::executeable(void)
{
	return true;
}

void StateFollowRoute::enter()
{
	// Reset timer variables
	now = then = device->getTimer()->getTime();
	timer = 0;

	// Determine closest point in route to NPC
	float nearestPointDistance = FLT_MAX;
	for (unsigned int i = 0; i < route.size(); i++)
	{
		float pathDistance = 0;

		// Calculate walking distance to each point
		std::vector<irr::core::vector3df> path = pathUtil->returnPath(&stateOwner->getPosition(), &route.at(i).first);
		if (!path.empty() && path.size() > 1)
		{
			for (unsigned int j = 1; j < path.size(); j++)
			{
				pathDistance += path.at(j-1).getDistanceFrom(path.at(j));
			}
			// Pick the point with the smallest distance to NPC
			if (pathDistance < nearestPointDistance)
			{
				nearestPointDistance = pathDistance;
				pointToVisit = i;
			}
		}
	}
}

void StateFollowRoute::exit()
{
}

void StateFollowRoute::action()
{
	updateDeltaTime();

	// Get a path from the state owner's position to the first point in the route
	std::vector<irr::core::vector3df> path = pathUtil->returnPath(&stateOwner->getPosition(), &(route.at(pointToVisit).first));

	// If there is a path to the next point
	if (!path.empty() && path.size() > 1)
	{
		// Move to it
		if (stateOwner->getPosition().getDistanceFrom(path.at(1)) > offset)
		{
			// Call callback method - boolean is false, not waiting at a point
			callbackFunction(&std::make_pair(false, &path.at(1)));
		}
		// If the point is reached
		else
		{
			// Callback method - boolean is true, waiting at a point
			callbackFunction(&std::make_pair(true, &path.at(1)));

			// Increase timer
			timer += frameDeltaTime;

			// Wait for an amount of time if specified
			if (timer >= route.at(pointToVisit).second)
			{
				if (++pointToVisit >= route.size())
					pointToVisit = 0;
				timer = 0;
			}
		}
	}
}

void StateFollowRoute::updateDeltaTime()
{
	now = device->getTimer()->getTime();
	frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;
}