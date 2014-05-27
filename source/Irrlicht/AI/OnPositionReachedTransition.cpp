#include "ai\OnPositionReachedTransition.h"

OnPositionReachedTransition::OnPositionReachedTransition(Detectable *owner, irr::core::vector3df position)
	: owner(owner), position(position), deviation(100), Transition()
{
}

OnPositionReachedTransition::OnPositionReachedTransition(Detectable *owner, irr::core::vector3df position, State* state)
	: owner(owner), position(position), deviation(100), Transition(state)
{
}

OnPositionReachedTransition::OnPositionReachedTransition(Detectable *owner, irr::core::vector3df position, irr::f32 deviation)
	: owner(owner), position(position), deviation(deviation), Transition()
{
}

OnPositionReachedTransition::OnPositionReachedTransition(Detectable *owner, irr::core::vector3df position, irr::f32 deviation, State* state)
	: owner(owner), position(position), deviation(deviation), Transition(state)
{
}

OnPositionReachedTransition::~OnPositionReachedTransition()
{
}

bool OnPositionReachedTransition::condition()
{
	return owner->getPosition().getDistanceFrom(position) <= deviation;
}