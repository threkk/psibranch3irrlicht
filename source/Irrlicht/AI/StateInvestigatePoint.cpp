#include "ai/StateInvestigatePoint.h"

StateInvestigatePoint::StateInvestigatePoint(Detectable* stateOwner, irr::core::vector3df* point, float attentionSpan, float visionLength, float offset,
	irr::scene::ISceneManager* sceneManager, irr::IrrlichtDevice* device, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, 
	IPathfinding* pathUtil, StateMachine* stateMachine)
{
	this->stateOwner = stateOwner;
	this->attentionSpan = attentionSpan;
	this->visionLength = visionLength;
	this->offset = offset;
	this->sceneManager = sceneManager;
	this->device = device;
	this->callbackFunction = callbackFunction;
	this->pathUtil = pathUtil;
	this->stateMachine = stateMachine;

	now = then = device->getTimer()->getTime();
	timer = 0;
}

StateInvestigatePoint::~StateInvestigatePoint(void)
{

}

bool StateInvestigatePoint::executeable(void)
{
	return true;
}

void StateInvestigatePoint::enter()
{
	// Reset timer variables
	now = then = device->getTimer()->getTime();
	timer = 0;
}

void StateInvestigatePoint::exit()
{
}

void StateInvestigatePoint::action()
{
	updateDeltaTime();

	// If NPC can see the point
	if (stateOwner->getPosition().getDistanceFrom(point) <= visionLength)
	{
		// Call callback method - boolean is true, NPC can see the point, vector is the position of the point
		callbackFunction(&std::make_pair(true, &point));

		// Increase the timer
		timer += frameDeltaTime;

		// If the timer is larger than the amount of time the NPC wants to look at the point
		if (timer >= attentionSpan)
		{
			timer = 0;
			// Return to the state previous to this one
			stateMachine->returnToPreviousState();
			return;
		}
	}
	// If NPC can't see the point
	else
	{
		// Get a path from the state owner's position to the point of interest
		std::vector<irr::core::vector3df> path = pathUtil->returnPath(&this->stateOwner->getPosition(), &point);

		// If there is a path
		if (!path.empty() && path.size() > 1)
		{
			// Move to it
			if (this->stateOwner->getPosition().getDistanceFrom(point) > offset)
			{
				// Call callback method - boolean is false, NPC can't see the point
				callbackFunction(&std::make_pair(false, &path.at(1)));
			}
		}
		timer = 0;
	}
}

void StateInvestigatePoint::updateDeltaTime()
{
	now = device->getTimer()->getTime();
	frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;
}