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
	Detectable* owner;
	Detectable* target;
	irr::scene::ISceneManager* sceneMgr;
	IPathfinding* pathUtil;

	/** Inherited Methods **/
	void action();
private:
	std::function<void(irr::core::vector3df)> callbackFunction;
};

