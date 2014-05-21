#pragma once

#include "ai\Transition.h"
#include "AI\Detectable.h"
#include "ISceneManager.h"

/**
 * On Target Lost Transition
 * Will check if the target can be seen. If not it it will check again for a short period time.
 * If the target can be found after the given time, the target is lost and the transition returns true.
 */

class __declspec(dllexport) OnTargetLostTransition: public Transition
{
public:
	OnTargetLostTransition(Detectable *owner, Detectable* target, float timeSpan,  ISceneManager* sceneMgr, irr::IrrlichtDevice* device);
	OnTargetLostTransition(Detectable *owner, Detectable* target,  float timeSpan, ISceneManager* sceneMgr, irr::IrrlichtDevice* device, State* state);
	~OnTargetLostTransition();

	bool condition();
	
	void setOwner(Detectable *owner);
	void setTarget(Detectable *target);

	/** Overwritten Methods **/
	void reset();

private:
	Detectable *owner, *target;
	ISceneManager* sceneMgr;

	// How long state owner should search for the target
	float timeSpan;

	// Irrlicht device
	irr::IrrlichtDevice* device;

	// Timer variables
	irr::u32 now;
	irr::u32 then;
	irr::f32 frameDeltaTime;
	irr::f32 timer;
};
