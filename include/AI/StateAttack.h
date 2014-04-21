#pragma once

#include "ai/State.h"
#include <functional>
#include "ai/Detectable.h"
#include "ai/ILiving.h"

/**
 * StateAttack
 * This state can be used for NPCs that will attack a living target, if it is alive and
 * near enough to attack.
 */
class __declspec(dllexport) StateAttack: public State
{
public:
	StateAttack(Detectable* stateOwner, ILiving* target, irr::scene::ISceneManager* sceneMgr,
		std::function<void(void*)> callbackFunction, void* callbackParameter);
	~StateAttack(void);

	/** Inherited Methods **/
	bool executeable(void);
	void enter();
	void exit();
protected:
	Detectable* owner;
	ILiving* target;
	irr::scene::ISceneManager* sceneMgr;
	std::function<void(void*)> callbackFunction;
	void* callbackParameter;

	/** Inherited Methods **/
	void action();
};

