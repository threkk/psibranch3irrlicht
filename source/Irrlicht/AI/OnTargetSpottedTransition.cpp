#include "ai\OnTargetSpottedTransition.h"

OnTargetSpottedTransition::OnTargetSpottedTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr, IPathfinding *pathfinding)
	: owner(owner), target(target), sceneMgr(sceneMgr), pathfinding(pathfinding), Transition()
{
}

OnTargetSpottedTransition::OnTargetSpottedTransition(Detectable *owner, Detectable* target, ISceneManager *sceneMgr, IPathfinding *pathfinding, State* state)
	: owner(owner), target(target), sceneMgr(sceneMgr), pathfinding(pathfinding), Transition(state)
{
}

OnTargetSpottedTransition::~OnTargetSpottedTransition()
{
}

bool OnTargetSpottedTransition::condition()
{
	if ( target == NULL || owner == NULL || sceneMgr == NULL ) return false;

	std::vector<irr::core::vector3df> path;
	return (owner->isObjectInfront(target, sceneMgr) && pathfinding->returnPath(&owner->getGroundPosition(), &target->getGroundPosition(), &path));
}

void OnTargetSpottedTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetSpottedTransition::setTarget(Detectable *target)
{
	this->target = target;
}