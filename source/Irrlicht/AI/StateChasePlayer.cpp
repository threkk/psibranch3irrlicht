#include "StateChasePlayer.h"
#include <vector>

StateChasePlayer::StateChasePlayer(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
	std::function<void(irr::core::vector3df)> callbackFunction, IPathfinding* pathUtil)
{
	this->owner = stateOwner;
	this->target = target;
	this->sceneMgr = sceneMgr;

	this->callbackFunction = callbackFunction;
	this->pathUtil = pathUtil;
}


StateChasePlayer::~StateChasePlayer(void)
{
}

bool StateChasePlayer::executeable(void)
{
	// The state will execute as soon as the player is seen
	return owner->isObjectVisible(target, sceneMgr);
}

void StateChasePlayer::action()
{
	// Get position of object
	std::vector<irr::core::vector3df> path = pathUtil->returnPath(&this->owner->getPosition(), &this->target->getPosition());

	if ( !path.empty() && path.size() > 1 )
	{
		// Call callback method
		if (this->owner->getPosition().getDistanceFrom(this->target->getPosition()) > 100)
		{
			callbackFunction(path.at(1));
		}
	}
}