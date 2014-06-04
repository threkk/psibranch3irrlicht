#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"

/**
 * Checks if the target is in range
 */
class __declspec(dllexport) OnTargetInRangeTransition: public Transition
{
public:
	OnTargetInRangeTransition(Detectable *owner, Detectable* target);
	OnTargetInRangeTransition(Detectable *owner, Detectable* target, State* state);
	OnTargetInRangeTransition(Detectable *owner, Detectable* target, irr::f32 range);
	OnTargetInRangeTransition(Detectable *owner, Detectable* target, irr::f32 range, State* state);
	~OnTargetInRangeTransition();

	bool condition();
	
	void setOwner(Detectable *owner);
	void setTarget(Detectable *target);
	void setRange(irr::f32 range);

private:
	Detectable *owner, *target;
	irr::f32 range;
};

