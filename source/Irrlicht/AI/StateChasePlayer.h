#include "State.h"
#include "Detectable.h"
#include "IPathfinding.h"
#include <functional>

#pragma once
class StateChasePlayer: public State
{
public:
	StateChasePlayer(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr, 
		std::function<void(irr::core::vector3df)> callbackFunction, IPathfinding* pathUtil);
	~StateChasePlayer(void);

	/** Inherited Methods **/
	bool executeable(void);
protected:
	// The owner of the state
	Detectable* owner;

	// The target object (mostly the player)
	Detectable* target;

	// The irrlicht scene manager (needed for ray collision detection)
	irr::scene::ISceneManager* sceneMgr;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function
	std::function<void(irr::core::vector3df)> callbackFunction;

	/** Inherited Methods **/
	void action();
};

