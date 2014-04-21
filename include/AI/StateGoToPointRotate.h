#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include "ai/StateMachine.h"
#include <functional>

#pragma once

/**
 * StateGoToPointRotate
 * This state can be used for NPCs to go to an point and then turn around.
 */
class __declspec(dllexport) StateGoToPointRotate: public State
{
public:
	StateGoToPointRotate(Detectable* stateOwner, irr::core::vector3df* point, irr::core::vector3df* rotation,
		std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, IPathfinding* pathUtil, StateMachine* stateMachine);
	~StateGoToPointRotate(void);

	/** Inherited methods **/
	virtual bool executeable(void);
	virtual void enter();
	virtual void exit();
protected:
	// The owner of the state
	Detectable* stateOwner;

	// The point to visit
	irr::core::vector3df* point;

	// Orientation after getting to point
	irr::core::vector3df* rotation;

	// The state machine
	StateMachine* stateMachine;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function - boolean indicates if point is reached
	std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction;

	/** Inherited methods **/
	void action();
};