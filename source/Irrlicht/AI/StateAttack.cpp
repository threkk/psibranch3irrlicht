#include "ai/StateAttack.h"



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
	return owner->isObjectInfront(target, sceneMgr, 100);
}

void StateAttack::enter()
{
}

void StateAttack::exit()
{
}

void StateAttack::action()
{
	callbackFunction(callbackParameter);
}