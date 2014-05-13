#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"

class __declspec(dllexport) OnTargetInRangeTransition: public Transition
{
public:
	OnTargetInRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr);
	OnTargetInRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, State* state);
	~OnTargetInRangeTransition();

	bool condition();
	
	void setOwner(Detectable *owner);
	void setTarget(Detectable *target);

private:
	Detectable *owner, *target;
	ISceneManager* sceneMgr;
};

