#include "ai/StateFollowRoute.h"


StateFollowRoute::StateFollowRoute(Detectable* stateOwner, std::vector<std::pair<irr::core::vector3df, float>>* route, IrrlichtDevice* device,
	IPathfinding* pathUtil, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction)
{
	this->stateOwner = stateOwner;
	this->route = *route;
	this->device = device;
	this->pathUtil = pathUtil;

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
	now = then = device->getTimer()->getTime();
	timer = 0;

	// Determine closest point in route
	float nearestPointDistance = FLT_MAX;

	for (unsigned int i = 0; i < route.size(); i++)
	{
		float pathDistance = 0;

		std::vector<irr::core::vector3df> path = pathUtil->returnPath(&stateOwner->getPosition(), &route.at(i).first);
		for (unsigned int j = 1; j < path.size(); j++)
		{
			pathDistance += path.at(j-1).getDistanceFrom(path.at(j));
		}

		if (pathDistance < nearestPointDistance)
		{
			nearestPointDistance = pathDistance;
			pointToVisit = i;
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
		if (stateOwner->getPosition().getDistanceFrom(path.at(1)) > 150)
		{
			// Call callback method
			callbackFunction(&std::make_pair(false, &path.at(1)));
		}
		// If the point is reached
		else
		{
			callbackFunction(&std::make_pair(true, &path.at(1)));

			timer += frameDeltaTime;

			if (timer >= route.at(pointToVisit).second)
			{
				++pointToVisit >= route.size() ? pointToVisit = 0 : NULL;
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