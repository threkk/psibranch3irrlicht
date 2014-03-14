#include "Detectable.h"
#include <cmath>
#include <iostream>

Detectable::~Detectable(void)
{
}

bool Detectable::isObjectVisible(Detectable* object, irr::scene::ISceneManager* sceneMgr)
{
	// get forward vector
	irr::core::vector3df direction = irr::core::vector3df(0, 0, 1);
	irr::core::matrix4 mat;
	mat.setRotationDegrees(this->getRotation());
	mat.transformVect(direction);

	// if point is too far away to see
	if (this->getPosition().getDistanceFrom(irr::core::vector3df(object->getPosition().X, 0, object->getPosition().Z) /* object->getPosition() */) > visionLength)
		return false;

	// get difference vector between object and me
	irr::core::vector3df difference = irr::core::vector3df(object->getPosition().X, 0, object->getPosition().Z) - this->getPosition();

	// if point is not in FoV
	if (direction.dotProduct(difference.normalize()) < cos(FOVRadian))
		return false;

	// skip raycast as it isn't working for now..
	return isObjectInfront(object, sceneMgr, visionLength);
}

bool Detectable::isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr)
{
	return isObjectInfront(object, sceneMgr, 130);
}

bool Detectable::isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr, irr::f32 visionLength)
{
	// get distance between object and me
	irr::core::vector3df difference = object->getPosition() - this->getPosition();

	// if point is too far away to see
	if (std::abs(difference.getLength()) > visionLength)
		return false;

	// ray cast for oject collision (TODO: Improve it for objects with mashes)
	irr::core::line3d<irr::f32> ray;
	ray.start = object->getPosition() /* + offset (cast ray from npc eyes) */;
	//ray.end = object->getPosition() /* + offset (cast ray to center of object) */;
	ray.end = object->getPosition() + (this->getPosition() - ray.start).normalize() * visionLength ;

	irr::scene::ISceneNode* selectedSceneNode = sceneMgr->getSceneCollisionManager()->getSceneNodeFromRayBB(ray);
		//->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle); // Don't use this method because the ID will be -1
	
	if (selectedSceneNode != NULL && selectedSceneNode->getID() == this->getNodeID())
	{
		// I can see the object!
		return true;
	}
	// I can't see anything or I see something different
	return false;
}