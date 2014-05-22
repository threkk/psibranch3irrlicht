#include "ai\OnTargetOutOfRangeTransition.h"

OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target)
	: owner(owner), target(target), range(110), Transition()
{
}

OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, State* state)
	: owner(owner), target(target), range(110), Transition(state)
{
}

OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, irr::f32 range)
	: owner(owner), target(target), range(range), Transition()
{
}
OnTargetOutOfRangeTransition::OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, irr::f32 range, State* state)
	: owner(owner), target(target), range(range), Transition(state)
{
}

OnTargetOutOfRangeTransition::~OnTargetOutOfRangeTransition()
{
}

bool OnTargetOutOfRangeTransition::condition()
{
	if ( target == NULL || owner == NULL ) return false;
	return !(owner->isObjectClose(target, range));
}

void OnTargetOutOfRangeTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetOutOfRangeTransition::setTarget(Detectable *target)
{
	this->target = target;
}