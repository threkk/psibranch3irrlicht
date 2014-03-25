#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include <functional>

#pragma once
class __declspec(dllexport) StateChasePlayer: public State
{
public:
	StateChasePlayer(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
		std::function<void(irr::core::vector3df*)> callbackFunction, IPathfinding* pathUtil);
	~StateChasePlayer(void);

	/** Inherited Methods **/
	bool executeable(void);
	void enter();
	void exit();
protected:
	// The owner of the state
	Detectable* owner;

	// The target object (mostly the player)
	Detectable* target;
	
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

