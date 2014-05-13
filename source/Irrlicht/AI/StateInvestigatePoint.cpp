#include "ai/StateInvestigatePoint.h"

StateInvestigatePoint::StateInvestigatePoint(Detectable* stateOwner, irr::core::vector3df* point, float visionLength, float offset,
	std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, 
	IPathfinding* pathUtil)
{
	this->stateOwner = stateOwner;
	this->offset = offset;
	this->visionLength = visionLength;
	this->callbackFunction = callbackFunction;
	this->pathUtil = pathUtil;
	if ( point != NULL ) this->point = *point;
}

StateInvestigatePoint::~StateInvestigatePoint(void)
{
}

void StateInvestigatePoint::enter()
{
}

void StateInvestigatePoint::exit()
{
}

void StateInvestigatePoint::setPoint(irr::core::vector3df point)
{
	this->point = point;
}

void StateInvestigatePoint::action()
{
	// If NPC can see the point
	if (stateOwner->getPosition().getDistanceFrom(point) <= visionLength)
	{
		// Call callback method - boolean is true, NPC can see the point, vector is the position of the point
		callbackFunction(&std::make_pair(true, &point));

	} else {
		// Get a path from the state owner's position to the point of interest
		std::vector<irr::core::vector3df> path = pathUtil->returnPath(&this->stateOwner->getPosition(), &point);

		// If there is a path
		if (!path.empty() && path.size() > 1)
		{
			// Move to it
			if (this->stateOwner->getPosition().getDistanceFrom(point) > offset)
			{
				// Call callback method - boolean is false, NPC can't see the point
				callbackFunction(&std::make_pair(false, &path.at(1)));
			}
		}
	}
}