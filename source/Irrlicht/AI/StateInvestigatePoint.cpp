#include "ai/StateInvestigatePoint.h"

StateInvestigatePoint::StateInvestigatePoint(Detectable* stateOwner, irr::core::vector3df* point, float attentionSpan, float visionLength,
	irr::scene::ISceneManager* sceneManager, irr::IrrlichtDevice* device, std::function<void(std::pair<bool, irr::core::vector3df*>*)> callbackFunction, 
	IPathfinding* pathUtil, StateMachine* stateMachine)
{
	this->stateOwner = stateOwner;
	this->point = point;
	this->attentionSpan = attentionSpan;
	this->visionLength = visionLength;
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
	now = then = device->getTimer()->getTime();
	timer = 0;
	//printf("StateInvestigatePoint::enter()\n");
}

void StateInvestigatePoint::exit()
{
	//printf("StateInvestigatePoint::exit()\n");
}

void StateInvestigatePoint::action()
{
	updateDeltaTime();
	/*irr::core::line3d<irr::f32> ray;
	ray.start = stateOwner->getPosition();
	ray.end = stateOwner->getPosition() + (*point - ray.start).normalize() * visionLength;

	irr::core::vector3df collisionPoint;
	irr::core::triangle3df triangle;
	irr::scene::ISceneNode* selectedSceneNode = sceneManager->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, collisionPoint, triangle);*/

	//printf("Collision point: %f, %f, %f\n", collisionPoint.X, collisionPoint.Y, collisionPoint.Z);
	//printf("stateOwner pos: %f, %f, %f\n", stateOwner->getPosition().X, stateOwner->getPosition().Y, stateOwner->getPosition().Z);
	//printf("Collision point -> noise distance: %f\n", collisionPoint.getDistanceFrom(*point));
	//printf("stateOwner -> collision point distance: %f\n", stateOwner->getPosition().getDistanceFrom(collisionPoint));

	//if (collisionPoint.getDistanceFrom(*point) <= 50)
	if (stateOwner->getPosition().getDistanceFrom(*point) <= visionLength / 2)
	{
		callbackFunction(&std::make_pair(true, point));

		timer += frameDeltaTime;

		if (timer >= attentionSpan)
		{
			timer = 0;
			stateMachine->returnToPreviousState();
			return;
		}
	}
	else
	{
		std::vector<irr::core::vector3df> path = pathUtil->returnPath(&this->stateOwner->getPosition(), point);

		if (!path.empty())
		{
			if (this->stateOwner->getPosition().getDistanceFrom(*point) > 100)
			{
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