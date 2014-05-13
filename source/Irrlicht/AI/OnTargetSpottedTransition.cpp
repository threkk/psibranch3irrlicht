#include "ai\OnTargetSpottedTransition.h"

OnTargetSpottedTransition::OnTargetSpottedTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr)
	: owner(owner), target(target), sceneMgr(sceneMgr), Transition()
{
}

OnTargetSpottedTransition::OnTargetSpottedTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr, State* state)
	: owner(owner), target(target), sceneMgr(sceneMgr), Transition(state)
{
}

OnTargetSpottedTransition::~OnTargetSpottedTransition()
{
}

bool OnTargetSpottedTransition::condition()
{
	if ( target == NULL || owner == NULL || sceneMgr == NULL ) return false;

	// The state will execute as soon as the player is seen
	if(owner->isObjectInfront(target, sceneMgr))
	{
		//hasSeen = true;
		//lastPointSeen = this->target->getPosition();
		return true;
	}
	return false;
	//If the player is not seen check if there is a lastPointSeen
	/*else if(hasSeen || hasLastPointSeen)
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
	}*/
}

void OnTargetSpottedTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetSpottedTransition::setTarget(Detectable *target)
{
	this->target = target;
}