#include "ai\OnPositionNotReachedTransition.h"

OnPositionNotReachedTransition::OnPositionNotReachedTransition(Detectable *owner, irr::core::vector3df position)
	: owner(owner), position(position), deviation(100), Transition()
{
}

OnPositionNotReachedTransition::OnPositionNotReachedTransition(Detectable *owner, irr::core::vector3df position, State* state)
	: owner(owner), position(position), deviation(100), Transition(state)
{
}

OnPositionNotReachedTransition::OnPositionNotReachedTransition(Detectable *owner, irr::core::vector3df position, irr::f32 deviation)
	: owner(owner), position(position), deviation(deviation), Transition()
{
}

OnPositionNotReachedTransition::OnPositionNotReachedTransition(Detectable *owner, irr::core::vector3df position, irr::f32 deviation, State* state)
	: owner(owner), position(position), deviation(deviation), Transition(state)
{
}

OnPositionNotReachedTransition::~OnPositionNotReachedTransition()
{
}

bool OnPositionNotReachedTransition::condition()
{
	return owner->getPosition().getDistanceFrom(position) > deviation;
}