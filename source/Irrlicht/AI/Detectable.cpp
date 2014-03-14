#include "Detectable.h"
#include <cmath>
#include <iostream>

Detectable::~Detectable(void)
{
}

bool Detectable::isObjectVisible(Detectable* object, irr::scene::ISceneManager* sceneMgr)
{
	// Get forward vector
	irr::core::vector3df direction = irr::core::vector3df(0, 0, 1);
	irr::core::matrix4 mat;
	mat.setRotationDegrees(this->getRotation());
	mat.transformVect(direction);

	// Get difference vector between object and me
	irr::core::vector3df difference = irr::core::vector3df(object->getPosition().X, 0, object->getPosition().Z) - this->getPosition();

	// If the object is not in the field of view return false
	if (direction.dotProduct(difference.normalize()) < cos(FOVRadian))
		return false;

	// Check for the raycast
	return isObjectInfront(object, sceneMgr, visionLength);
}

bool Detectable::isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr)
{
	return isObjectInfront(object, sceneMgr, 130);
}

bool Detectable::isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr, irr::f32 visionLength)
{
	// TODO Improve ray cast for objects with meshes, so that it won't collide with it's own mesh
	// TODO Improve ray cast so that it cannot go through walls

	// get distance between object and me
	irr::core::vector3df difference = object->getPosition() - this->getPosition();

	// if point is too far away to see
	if (this->getPosition().getDistanceFrom(object->getPosition()) > visionLength)
		return false;

	// Shoot an ray from the target to this object to check if the player can be seen
	irr::core::line3d<irr::f32> ray;
	ray.start = object->getPosition();
	ray.end = object->getPosition() + (this->getPosition() - ray.start).normalize() * visionLength ;

	// Get the scene node that will be hit from the ray
	irr::scene::ISceneNode* selectedSceneNode = sceneMgr->getSceneCollisionManager()->getSceneNodeFromRayBB(ray);
	
	// If the found node has the same ID as the searched node, the object can be seen
	if (selectedSceneNode != NULL && selectedSceneNode->getID() == this->getNodeID())
	{
		// Object can be seen
		return true;
	}
	// No object or another object is seen
	return false;
}