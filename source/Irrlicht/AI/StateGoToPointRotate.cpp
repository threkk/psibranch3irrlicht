#include "ai/StateGoToPointRotate.h"

StateGoToPointRotate::StateGoToPointRotate(Detectable* stateOwner, irr::core::vector3df* point, irr::core::vector3df* rotation, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine)
{
	this->stateOwner = stateOwner;
	this->point = point;
	this->rotation = rotation;
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
	std::vector<irr::core::vector3df> path = pathUtil->returnPath(&stateOwner->getPosition(), &irr::core::vector3df(point->X, stateOwner->getPosition().Y, point->Z));

	if (!path.empty() && path.size() > 1)
	{
		if (this->stateOwner->getPosition().getDistanceFrom(*point) > 100)
		{
			callbackFunction(&std::make_pair(false, &path.at(1)));
		}
		else
		{
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
