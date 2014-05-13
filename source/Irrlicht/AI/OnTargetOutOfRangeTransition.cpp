#include "ai\OnTargetOutOfRangeTransition.h"

OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr)
	: owner(owner), target(target), sceneMgr(sceneMgr), Transition()
{
}

OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr, State* state)
	: owner(owner), target(target), sceneMgr(sceneMgr), Transition(state)
{
}

OnTargetOutOfRangeTransition::~OnTargetOutOfRangeTransition()
{
}

bool OnTargetOutOfRangeTransition::condition()
{
	if ( target == NULL || owner == NULL || sceneMgr == NULL ) return false;
	return !(owner->isObjectInfront(target, sceneMgr, 110));
}

void OnTargetOutOfRangeTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetOutOfRangeTransition::setTarget(Detectable *target)
{
	this->target = target;
}