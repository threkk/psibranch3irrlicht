#include "ai/StateChaseTarget.h"
#include <vector>
#include "ai/StateMachine.h"

StateChaseTarget::StateChaseTarget(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
	std::function<void(irr::core::vector3df*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine)
	: StateFollowTarget(stateOwner, target, sceneMgr, callbackFunction, pathUtil, stateMachine)
{
	
}

StateChaseTarget::~StateChaseTarget(void)
{
}

void StateChaseTarget::action()
{
	if ( owner == NULL || target == NULL ) return;

	// Get the position of the target
	irr::core::vector3df toPos;
	if(hasSeen)
	{
		toPos = this->target->getGroundPosition();
	}
	else if(hasLastPointSeen)
	{
		// or at least the last of the target
		toPos = lastPointSeen;
	}
	else
	{
		return;
	}
	// Get the path of object by the pathfinding utility
	std::vector<irr::core::vector3df> path = pathUtil->returnPath(&this->owner->getPosition(), &toPos);
	
	// If there is a path to the object walk to it
	if ( !path.empty() && path.size() > 1 )
	{
		// Don't walk right into the target
		if (this->owner->getPosition().getDistanceFrom(irr::core::vector3df(toPos.X, toPos.Y, toPos.Z)) > 100)
		{
			// Call callback method
			callbackFunction(&path.at(1));
		}
		else
		{
			hasLastPointSeen = false;
			hasSeen = false;
			//stateMachine->returnToPreviousState();
		}
	}
}