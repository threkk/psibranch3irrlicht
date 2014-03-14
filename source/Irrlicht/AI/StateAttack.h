#include "State.h"
#include <functional>
#include "Detectable.h"

#pragma once
class StateAttack: public State
{
public:
	StateAttack(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr,
		std::function<void(void*)> callbackFunction, void* callbackParameter);
	~StateAttack(void);

	/** Inherited Methods **/
	bool executeable(void);
private:
	// The owner of the state
	Detectable* owner;

	// The target object (mostly the player)
	Detectable* target;

	// The irrlicht scene manager (needed for ray collision detection)
	irr::scene::ISceneManager* sceneMgr;

	// The callback function that will be called
	std::function<void(void*)> callbackFunction;

	// The callback parameters that will be forwarded to the callback function
	void* callbackParameter;

	/** Inherited Methods **/
	void action();
};

