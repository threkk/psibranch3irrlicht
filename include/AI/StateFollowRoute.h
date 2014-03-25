#include "ai/State.h"
#include "ai/Detectable.h"
#include "ai/IPathfinding.h"
#include <functional>

#pragma once
class __declspec(dllexport) StateFollowRoute : public State
{
public:
	StateFollowRoute(Detectable* stateOwner, std::vector<irr::core::vector3df>* route, IPathfinding* pathUtil,
		std::function<void(irr::core::vector3df*)> callbackFunction);
	~StateFollowRoute(void);

	/** Inherited Methods **/
	bool executeable(void);
	void enter();
	void exit();
private:
	Detectable* owner;

	// The route to be followed
	std::vector<irr::core::vector3df> *route;

	// The pathfinding utility
	IPathfinding* pathUtil;

	// The callback function
	std::function<void(irr::core::vector3df*)> callbackFunction;

	/** Inherited Methods **/
	void action();
};
