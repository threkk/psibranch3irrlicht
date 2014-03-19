#include "Detectable.h"
#include <cmath>
#include <iostream>

Detectable::~Detectable(void)
{
}


bool Detectable::isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr, irr::f32 visionLength)
{

	irr::core::vector3df direction = irr::core::vector3df(0, 0, 1);
	return isObjectVisible(object, sceneMgr, direction, visionLength);

}

bool Detectable::isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr)
{

	irr::core::vector3df direction = irr::core::vector3df(0, 0, 1);
	return isObjectVisible(object, sceneMgr, direction, visionLength);

}


bool Detectable::isObjectBehind(Detectable* object, irr::scene::ISceneManager* sceneMgr, irr::f32 visionLength)
{

	irr::core::vector3df direction = irr::core::vector3df(0, 0, -1);
	return isObjectVisible(object, sceneMgr, direction, visionLength);
}

bool Detectable::isObjectVisible(Detectable* object, irr::scene::ISceneManager* sceneMgr, irr::core::vector3df direction, irr::f32 visionLength){

	// get forward vector
	irr::core::matrix4 mat;
	mat.setRotationDegrees(this->getRotation());
	mat.transformVect(direction);

	// If point is too far away to see
	if (this->getPosition().getDistanceFrom(object->getPosition()) > visionLength)
		return false;

	// get difference vector between object and me
	irr::core::vector3df difference = object->getPosition() - this->getPosition();

	// if point is not in FoV
	if (direction.dotProduct(difference.normalize()) < cos(FOVRadian))
		return false;

	// Shoot an ray from the target to this object to check if the player can be seen
	irr::core::line3d<irr::f32> ray;
	ray.start = object->getPosition();
	ray.end = object->getPosition() + (this->getPosition() - ray.start).normalize() * visionLength ;

	// Get the scene node that will be hit from the ray
	irr::core::vector3df intersection;
	irr::core::triangle3df hitTriangle;
	irr::scene::ISceneNode * selectedSceneNode = sceneMgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle);
	
	// If the found node has the same ID as the searched node, the object can be seen
	if (selectedSceneNode && selectedSceneNode->getID() == this->getNodeID())
	{
		float f1 = this->getNodeID();
		float f2 = selectedSceneNode->getID();
		// Object can be seen
		printf("This id: %f     Selected id: %f\n",f1 ,f2);
		return true;
	}
	// No object or another object is seen
	return false;

}