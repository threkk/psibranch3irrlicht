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
	Detectable* owner;
	Detectable* target;
	irr::scene::ISceneManager* sceneMgr;
	std::function<void(void*)> callbackFunction;
	void* callbackParameter;

	/** Inherited Methods **/
	void action();
};

