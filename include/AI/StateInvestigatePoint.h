#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include "ai/StateMachine.h"
#include <functional>

#pragma once
/**
 * StateInvestigatePoint
 * This state can be used for NPCs to go to a point and look at it for a specified amount of time.
 */
class __declspec(dllexport) StateInvestigatePoint : public State
{
public:
	StateInvestigatePoint(Detectable* stateOwner, irr::core::vector3df* point, float visionLength, float offset,
		std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, 
		IPathfinding* pathUtil);
	~StateInvestigatePoint(void);

	void enter();
	void exit();

protected:
	// The owner of the state
	Detectable* stateOwner;

	// The point to investigate
	irr::core::vector3df point;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function
	std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction;

	// Distance value to stop NPC from walking right into the goal
	float offset;
	float visionLength;

	/** Overwritten methods **/
	void action();
};