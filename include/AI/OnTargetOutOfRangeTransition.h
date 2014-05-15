#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"

class __declspec(dllexport) OnTargetOutOfRangeTransition: public Transition
{
public:
	OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr);
	OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, State* state);
	OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, irr::f32 range);
	OnTargetOutOfRangeTransition(Detectable *owner, Detectable* target, ISceneManager* sceneMgr, irr::f32 range, State* state);
	~OnTargetOutOfRangeTransition();

	bool condition();

	void setOwner(Detectable *owner);
	void setTarget(Detectable *target);
	void setRange(irr::f32 range);

private:
	Detectable *owner, *target;
	ISceneManager* sceneMgr;
	irr::f32 range;
};

