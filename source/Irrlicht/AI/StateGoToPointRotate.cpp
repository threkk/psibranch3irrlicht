#include "ai/StateGoToPointRotate.h"

StateGoToPointRotate::StateGoToPointRotate(Detectable* stateOwner, irr::core::vector3df* point, irr::core::vector3df* rotation, float offset, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine)
{
	this->stateOwner = stateOwner;
	this->point = point;
	this->rotation = rotation;
	this->offset = offset;
	this->callbackFunction = callbackFunction;
	this->pathUtil = pathUtil;
	this->stateMachine = stateMachine;
}

StateGoToPointRotate::~StateGoToPointRotate(void)
{

}

bool StateGoToPointRotate::executeable(void)
{
	return true;
}

void StateGoToPointRotate::enter()
{
}

void StateGoToPointRotate::exit()
{
}

void StateGoToPointRotate::action()
{
	// Get a path from the state owner's position to the point
	std::vector<irr::core::vector3df> path = pathUtil->returnPath(&stateOwner->getPosition(), point);

	// If there is a path to the next point
	if (!path.empty() && path.size() > 1)
	{
		// Move to it
		if (this->stateOwner->getPosition().getDistanceFrom(*point) > offset)
		{
			// Call callback method - boolean is false, NPC has not reached point yet
			callbackFunction(&std::make_pair(false, &path.at(1)));
		}
		else
		{
			// Call callback method - boolean is true, NPC reached point
			callbackFunction(&std::make_pair(true, rotation));
			stateMachine->returnToPreviousState();
		}
	}
	else
	{
		// No path to point -> Return to previous state
		stateMachine->returnToPreviousState();
	}
}
