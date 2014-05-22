#include "ai\OnTargetInRangeTransition.h"

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target)
	: owner(owner), target(target), range(110), Transition()
{
}

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, State* state)
	: owner(owner), target(target), range(110), Transition(state)
{
}

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, irr::f32 range)
	: owner(owner), target(target), range(range), Transition()
{
}

OnTargetInRangeTransition::OnTargetInRangeTransition(Detectable *owner, Detectable* target, irr::f32 range, State* state)
	: owner(owner), target(target), range(range), Transition(state)
{
}

OnTargetInRangeTransition::~OnTargetInRangeTransition()
{
}

bool OnTargetInRangeTransition::condition()
{
	if ( target == NULL || owner == NULL ) return false;
	return (owner->isObjectClose(target, range));
}

void OnTargetInRangeTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetInRangeTransition::setTarget(Detectable *target)
{
	this->target = target;
}