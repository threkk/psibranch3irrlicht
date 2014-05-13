#include "ai/StateFollowTarget.h"
#include <vector>
#include "ai/StateMachine.h"

StateFollowTarget::StateFollowTarget(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
	std::function<void(irr::core::vector3df*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine)
{
	this->owner = stateOwner;
	this->target = target;
	this->sceneMgr = sceneMgr;
	this->stateMachine = stateMachine;

	this->callbackFunction = callbackFunction;
	this->pathUtil = pathUtil;
}


StateFollowTarget::~StateFollowTarget(void)
{
}

void StateFollowTarget::enter()
{
}

void StateFollowTarget::exit()
{
}

void StateFollowTarget::action()
{
	if ( owner == NULL || target == NULL ) return;

	// Get position of object by the pathfinding utility
	std::vector<irr::core::vector3df> path = pathUtil->returnPath(&this->owner->getPosition(), &this->target->getGroundPosition());
	
	// If there is a path to the object walk to it
	if ( !path.empty() && path.size() > 1 )
	{
		// Don't walk right into the target
		if (this->owner->getPosition().getDistanceFrom(this->target->getGroundPosition()) > 100)
		{
			// Call callback method
			callbackFunction(&path.at(1));
		}
	}
}

void StateFollowTarget::noActionFallback()
{
	stateMachine->returnToPreviousState();
}

void StateFollowTarget::setTarget(Detectable *target)
{
	this->target = target;
}

void StateFollowTarget::setOwner(Detectable *owner)
{
	this->owner = owner;
}