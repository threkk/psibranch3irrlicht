#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include "ai/StateMachine.h"
#include <functional>

#pragma once
class __declspec(dllexport) StateFollowTarget: public State
{
public:
	StateFollowTarget(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
		std::function<void(irr::core::vector3df*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine);
	~StateFollowTarget(void);

	/** Inherited Methods **/
	virtual bool executeable(void);
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