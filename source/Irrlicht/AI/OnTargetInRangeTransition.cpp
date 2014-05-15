#include "ai\OnTargetInRangeTransition.h"

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr)
	: owner(owner), target(target), sceneMgr(sceneMgr), range(110), Transition()
{
}

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr, State* state)
	: owner(owner), target(target), sceneMgr(sceneMgr), range(110), Transition(state)
{
}

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, irr::f32 range)
	: owner(owner), target(target), sceneMgr(sceneMgr), range(range), Transition()
{
}

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, irr::f32 range, State* state)
	: owner(owner), target(target), sceneMgr(sceneMgr), range(range), Transition(state)
{
}

OnTargetInRangeTransition::~OnTargetInRangeTransition()
{
}

bool OnTargetInRangeTransition::condition()
{
	if ( target == NULL || owner == NULL || sceneMgr == NULL ) return false;
	return (owner->isObjectInfront(target, sceneMgr, range));
}

void OnTargetInRangeTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetInRangeTransition::setTarget(Detectable *target)
{
	this->target = target;
}