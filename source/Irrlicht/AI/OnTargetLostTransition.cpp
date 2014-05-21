#include "ai\OnTargetLostTransition.h"

OnTargetLostTransition::OnTargetLostTransition(Detectable *owner, Detectable* target, float timeSpan,
	ISceneManager *sceneMgr, irr::IrrlichtDevice* device)
	:owner(owner), target(target), timeSpan(timeSpan), sceneMgr(sceneMgr), device(device), Transition()
{
}

OnTargetLostTransition::OnTargetLostTransition(Detectable *owner, Detectable* target, float timeSpan,
	ISceneManager *sceneMgr, irr::IrrlichtDevice* device, State* state)
	: owner(owner), target(target), timeSpan(timeSpan), sceneMgr(sceneMgr), device(device), Transition(state)
{
}

OnTargetLostTransition::~OnTargetLostTransition()
{
}

bool OnTargetLostTransition::condition()
{
	if ( target == NULL || owner == NULL || sceneMgr == NULL ) return false;

	// Update timer
	now = device->getTimer()->getTime();
	frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;

	// If target cannot be seen
	if(!owner->isObjectInfront(target, sceneMgr))
	{
		// Increase the timer
		timer += frameDeltaTime;
		
		printf("TIMER %f\n", timer);
		if (timer >= timeSpan)
		{
			return true;
		}
	} else {
		// Target can be seen, reset Timer()
		reset();

		// Save the position
		lastPosition = owner->getGroundPosition();
	}
	
	return false;
}

void OnTargetLostTransition::setOwner(Detectable *owner)
{
	this->owner = owner;
}

void OnTargetLostTransition::setTarget(Detectable *target)
{
	this->target = target;
}

void OnTargetLostTransition::reset()
{
	// Reset timer variables
	now = then = device->getTimer()->getTime();
	timer = 0;
}