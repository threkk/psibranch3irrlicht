#include "ai/StateAttack.h"



StateAttack::StateAttack(Detectable* stateOwner, ILiving* target, irr::scene::ISceneManager* sceneMgr,
	std::function<void(ILiving*, void*)> callbackFunction, void* callbackParameter)
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

void StateAttack::enter()
{
}

void StateAttack::exit()
{
}

void StateAttack::action()
{
	callbackFunction(target, callbackParameter);
}

void StateAttack::setOwner(Detectable* owner)
{
	this->owner = owner;
}

void StateAttack::setTarget(ILiving* target)
{
	this->target = target;
}