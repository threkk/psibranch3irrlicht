#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"

class __declspec(dllexport) OnTargetSpottedTransition: public Transition
{
public:
	OnTargetSpottedTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr);
	OnTargetSpottedTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, State* state);
	~OnTargetSpottedTransition();

	bool condition();
	
	void setOwner(Detectable *owner);
	void setTarget(Detectable *target);

private:
	Detectable *owner, *target;
	ISceneManager* sceneMgr;
};

