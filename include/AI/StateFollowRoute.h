#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include <functional>

#pragma once

/**
 * State follow route
 * This state can be used for NPCs that will follow a predefined route
 */
class __declspec(dllexport) StateFollowRoute : public State
{
public:
	StateFollowRoute(Detectable* stateOwner, std::vector<std::pair<irr::core::vector3df, float>>* route, float offset, IrrlichtDevice* device,
		IPathfinding* pathUtil, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction);
	~StateFollowRoute(void);

	void setRoute(std::vector<std::pair<irr::core::vector3df, float>> route);

	/** Inherited Methods **/
	void enter();
	void exit();
protected:
	Detectable* stateOwner;

	// The route to be followed
	std::vector<std::pair<irr::core::vector3df, float>> route;

	// Distance value to stop NPC from walking right into the goal
	float offset;

	// Timer variables
	irr::u32 now;
	irr::u32 then;
	irr::f32 frameDeltaTime;
	irr::f32 timer;

	// Next point to be visited
	unsigned int pointToVisit;

	// Pointer to Irrlicht device
	IrrlichtDevice* device;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function returns a pair of a boolean and vector
	// Boolean indicates if a NPC has reached a point in route and is waiting
	std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction;

	// Updates the delta time variable
	void updateDeltaTime();

	/** Inherited Methods **/
	void action();
};
