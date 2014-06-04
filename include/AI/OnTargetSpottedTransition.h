#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"
#include "IPathfinding.h"

/**
 * Checks if the owner can see the target
 */
class __declspec(dllexport) OnTargetSpottedTransition: public Transition
{
public:
	OnTargetSpottedTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, IPathfinding *pathfinding);
	OnTargetSpottedTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, IPathfinding *pathfinding, State* state);
	~OnTargetSpottedTransition();

	bool condition();
	
	void setOwner(Detectable *owner);
	void setTarget(Detectable *target);

private:
	IPathfinding *pathfinding;
	Detectable *owner, *target;
	ISceneManager* sceneMgr;
};

