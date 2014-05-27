#include "ai/Detectable.h"
#include <cmath>
#include <iostream>

Detectable::~Detectable(void)
{
}

Detectable::Detectable() : 
	visionLength(1000), 
	FOVRadian((atan(1.f)*4)/3), // 90°
	meshSize(0)
{
}

Detectable::Detectable(irr::f32 visionLength, irr::f32 FOVRadian, irr::f32 meshSize) :
	visionLength(visionLength),
	FOVRadian(FOVRadian),
	meshSize(meshSize)
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

	// Get forward vector
	irr::core::matrix4 mat;
	mat.setRotationDegrees(this->getRotation());
	mat.transformVect(direction);

	// Return false if point is too far away to see
	if (this->getPosition().getDistanceFrom(object->getPosition()) > visionLength)
	{
		return false;
	}

	// Get difference vector between object and me
	irr::core::vector3df difference = object->getPosition() - this->getPosition();

	// Return false if point is not in FoV (Field of view)
	if (direction.dotProduct(difference.normalize()) < cos(FOVRadian))
		return false;

	// Shoot an ray from the target to this object to check if the player can be seen
	irr::core::line3d<irr::f32> ray;
	ray.start = object->getPosition() + (this->getPosition() - object->getPosition()).normalize() * object->meshSize;
	ray.end = object->getPosition() + (this->getPosition() - ray.start).normalize() * visionLength ;

	// Get the scene node that will be hit from the ray
	irr::core::vector3df intersection;
	irr::core::triangle3df hitTriangle;
	irr::scene::ISceneNode * selectedSceneNode = sceneMgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle);
	
	// If the found node has the same ID as the searched node, the object can be seen
	if (selectedSceneNode && selectedSceneNode->getID() == this->getNodeID())
	{
		// Object can be seen
		return true;
	}
	// No object or another object is seen
	return false;
}

bool Detectable::isObjectClose(Detectable* object, irr::f32 visionLength)
{
	return (this->getPosition().getDistanceFrom(object->getPosition()) < visionLength);
}

bool Detectable::isPointVisible(irr::core::vector3df point, irr::scene::ISceneManager* sceneMgr)
{
	return isPointVisible(point, sceneMgr, irr::core::vector3df(0, 0, 1), this->visionLength);
}

bool Detectable::isPointVisible(irr::core::vector3df point, irr::scene::ISceneManager* sceneMgr, irr::core::vector3df direction, irr::f32 visionLength)
{
	// Get forward vector
	irr::core::matrix4 mat;
	mat.setRotationDegrees(this->getRotation());
	mat.transformVect(direction);

	// Return false if point is too far away to see
	if (this->getPosition().getDistanceFrom(point) > visionLength)
	{
		return false;
	}

	// Get difference vector between object and me
	irr::core::vector3df difference = point - this->getPosition();

	// Return false if point is not in FoV (Field of view)
	if (direction.dotProduct(difference.normalize()) < cos(FOVRadian))
		return false;

	// Shoot an ray from the target to this object to check if the player can be seen
	irr::core::line3d<irr::f32> ray;
	ray.start = point;
	ray.end = point + (this->getPosition() - ray.start).normalize() * visionLength ;

	// Get the scene node that will be hit from the ray
	irr::core::vector3df intersection;
	irr::core::triangle3df hitTriangle;
	irr::scene::ISceneNode * selectedSceneNode = sceneMgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, intersection, hitTriangle);
	
	// If the found node has the same ID as the searched node, the object can be seen
	if (selectedSceneNode && selectedSceneNode->getID() == this->getNodeID())
	{
		// Object can be seen
		return true;
	}
	// No object or another object is seen
	return false;
}