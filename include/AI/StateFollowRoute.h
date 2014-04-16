#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include <functional>

#pragma once
class __declspec(dllexport) StateFollowRoute : public State
{
public:
	StateFollowRoute(Detectable* stateOwner, std::vector<std::pair<irr::core::vector3df, float>>* route, IrrlichtDevice* device,
		IPathfinding* pathUtil, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction);
	~StateFollowRoute(void);

	/** Inherited Methods **/
	bool executeable(void);
	void enter();
	void exit();
protected:
	Detectable* stateOwner;

	// The route to be followed
	std::vector<std::pair<irr::core::vector3df, float>> route;

	// Timer stuff
	irr::u32 now;
	irr::u32 then;
	irr::f32 frameDeltaTime;
	irr::f32 timer;

	void updateDeltaTime();

	// Next point to be visited
	unsigned int pointToVisit;

	// Pointer to Irrlicht device
	IrrlichtDevice* device;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function
	std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction;

	/** Inherited Methods **/
	void action();
};
