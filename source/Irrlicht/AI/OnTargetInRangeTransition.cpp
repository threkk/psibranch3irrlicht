#include "ai\OnTargetInRangeTransition.h"

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr)
	: owner(owner), target(target), sceneMgr(sceneMgr), Transition()
{
}

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr, State* state)
	: owner(owner), target(target), sceneMgr(sceneMgr), Transition(state)
{
}

OnTargetInRangeTransition::~OnTargetInRangeTransition()
{
}

bool OnTargetInRangeTransition::condition()
{
	if ( target == NULL || owner == NULL || sceneMgr == NULL ) return false;
	return (owner->isObjectInfront(target, sceneMgr, 110));
}

void OnTargetInRangeTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetInRangeTransition::setTarget(Detectable *target)
{
	this->target = target;
}