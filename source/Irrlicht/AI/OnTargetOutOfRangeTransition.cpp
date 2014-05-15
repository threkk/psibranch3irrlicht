#include "ai\OnTargetOutOfRangeTransition.h"

OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr)
	: owner(owner), target(target), sceneMgr(sceneMgr), range(110), Transition()
{
}

OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr, State* state)
	: owner(owner), target(target), sceneMgr(sceneMgr), range(110), Transition(state)
{
}

OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, irr::f32 range)
	: owner(owner), target(target), sceneMgr(sceneMgr), range(range), Transition()
{
}
OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, irr::f32 range, State* state)
	: owner(owner), target(target), sceneMgr(sceneMgr), range(range), Transition(state)
{
}

OnTargetOutOfRangeTransition::~OnTargetOutOfRangeTransition()
{
}

bool OnTargetOutOfRangeTransition::condition()
{
	if ( target == NULL || owner == NULL || sceneMgr == NULL ) return false;
	return !(owner->isObjectInfront(target, sceneMgr, range));
}

void OnTargetOutOfRangeTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetOutOfRangeTransition::setTarget(Detectable *target)
{
	this->target = target;
}