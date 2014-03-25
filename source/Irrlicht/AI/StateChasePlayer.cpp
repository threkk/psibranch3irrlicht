#include "ai/StateChasePlayer.h"
#include <vector>
#include "ai/StateMachine.h"

StateChasePlayer::StateChasePlayer(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
	std::function<void(irr::core::vector3df*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine)
{
	this->owner = stateOwner;
	this->target = target;
	this->sceneMgr = sceneMgr;
	this->stateMachine = stateMachine;

	this->callbackFunction = callbackFunction;
	this->pathUtil = pathUtil;

	hasSeen = false;
	hasLastPointSeen = false;
}


StateChasePlayer::~StateChasePlayer(void)
{
}

bool StateChasePlayer::executeable(void)
{
	// The state will execute as soon as the player is seen
	if(owner->isObjectInfront(target, sceneMgr))
	{
		hasSeen = true;
		lastPointSeen = this->target->getPosition();
		return true;
	}
	//If the player is not seen check if there is a lastPointSeen
	else if(hasSeen || hasLastPointSeen)
	{
		hasSeen = false;
		hasLastPointSeen = true;
		return true;
	}
	//Otherwise return false
	else
	{
		hasSeen = false;
		hasLastPointSeen = false;
		return false;
	}
}

void StateChasePlayer::enter()
{
	printf("enter");
}

void StateChasePlayer::exit()
{
	printf("exit");
}

void StateChasePlayer::action()
{
	irr::core::vector3df toPos;
	if(hasSeen)
	{
		toPos = this->target->getGroundPosition();
	}
	else if(hasLastPointSeen)
	{
		toPos = lastPointSeen;
	}
	else
	{
		return;
	}
	// Get position of object by the pathfinding utility
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
			stateMachine->returnToPreviousState();
		}
	}
}