#include "ai/StateInvestigatePoint.h"

StateInvestigatePoint::StateInvestigatePoint(Detectable* stateOwner, irr::core::vector3df* point, float visionLength, 
	float offset, irr::scene::ISceneManager *sceneMgr,
	std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, 
	IPathfinding* pathUtil)
	: stateOwner(stateOwner), offset(offset), visionLength(visionLength), callbackFunction(callbackFunction), pathUtil(pathUtil), sceneMgr(sceneMgr)
{
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
	if ( stateOwner->isPointVisible(point, sceneMgr) )
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