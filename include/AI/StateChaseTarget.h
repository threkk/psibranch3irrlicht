#include "ai/State.h"
#include "ai/StateFollowTarget.h"
#include <functional>

#pragma once
/**
 * StateChaseTarget
 * This state can be used to chase a target as long it is seen.
 * If it doesn't see the target anymore, it will go to the point where the target has been seen last.
 */
class __declspec(dllexport) StateChaseTarget: public StateFollowTarget
{
public:
	StateChaseTarget(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
		std::function<void(irr::core::vector3df*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine);
	~StateChaseTarget(void);

	/** Inherited Methods **/
	virtual bool executeable(void);

protected:
	
	// The vector position of the location where the target is seen the last
	irr::core::vector3df lastPointSeen;

	// Bool if there is a lastPointSeen location
	bool hasLastPointSeen;

	// Bool to know if the target is seen that frame
	bool hasSeen;

	
	void action();
};