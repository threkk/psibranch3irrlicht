#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include "ai/StateMachine.h"
#include <functional>

#pragma once

/**
 * StateFollowTarget
 * This state can be used for NPCs that will follow a target even when they can't see it anymore.
 */
class __declspec(dllexport) StateFollowTarget: public State
{
public:
	StateFollowTarget(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
		std::function<void(irr::core::vector3df*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine);
	~StateFollowTarget(void);

	void setTarget(Detectable *target);
	void setOwner(Detectable *owner);

	/** Inherited Methods **/
	virtual void enter();
	virtual void exit();
protected:
	// The owner of the state
	Detectable* owner;

	// The target object (mostly the player)
	Detectable* target;
	
	StateMachine* stateMachine;
	

	// The irrlicht scene manager (needed for ray collision detection)
	irr::scene::ISceneManager* sceneMgr;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function
	std::function<void(irr::core::vector3df*)> callbackFunction;

	/** Inherited Methods **/
	void action();
	void noActionFallback();
};