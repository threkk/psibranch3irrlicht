#include "StateAttack.h"



StateAttack::StateAttack(Detectable* stateOwner, Detectable* target, irr::scene::ISceneManager* sceneMgr,
	std::function<void(void*)> callbackFunction, void* callbackParameter)
{
	this->owner = stateOwner;
	this->target = target;
	this->sceneMgr = sceneMgr;
	this->callbackFunction = callbackFunction;
	this->callbackParameter = callbackParameter;
}


StateAttack::~StateAttack(void)
{
}

bool StateAttack::executeable(void)
{
	// Only attack if target is directly in front of the object
	return owner->isObjectInfront(target, sceneMgr);
}

void StateAttack::action()
{
	// Execute callback function
	callbackFunction(callbackParameter);
}