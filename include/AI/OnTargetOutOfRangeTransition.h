#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"

class __declspec(dllexport) OnTargetOutOfRangeTransition: public Transition
{
public:
	OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr);
	OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, State* state);
	~OnTargetOutOfRangeTransition();

	bool condition();

	void setOwner(Detectable *owner);
	void setTarget(Detectable *target);

private:
	Detectable *owner, *target;
	ISceneManager* sceneMgr;
};

