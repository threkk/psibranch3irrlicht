#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include "ai/StateMachine.h"
#include <functional>

#pragma once
class __declspec(dllexport) StateChaseTarget: public State
{
public:
	StateChaseTarget(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
		std::function<void(irr::core::vector3df*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine);
	~StateChaseTarget(void);

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
	
	// The vector position of the location where the target is seen the last
	irr::core::vector3df lastPointSeen;

	// Bool if there is a lastPointSeen location
	bool hasLastPointSeen;

	// Bool to know if the target is seen that frame
	bool hasSeen;

	// The irrlicht scene manager (needed for ray collision detection)
	irr::scene::ISceneManager* sceneMgr;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function
	std::function<void(irr::core::vector3df*)> callbackFunction;

	/** Inherited Methods **/
	void action();
};