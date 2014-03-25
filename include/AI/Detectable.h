#include <irrlicht.h>

#pragma once

class __declspec(dllexport) Detectable
{
public:
	virtual ~Detectable(void);


	/**
	 * Checks if the target is infront of this class. Uses the passed vision length.
	 */
	bool isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr, irr::f32 visionLength);

	/**
	 * Checks if the target is infront of this class. Uses the vision length of this object.
	 */
	bool isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr);

	/**
	 * Checks if the target is behind of this class. Uses the passed vision length.
	 */
	bool isObjectBehind(Detectable* object, irr::scene::ISceneManager* sceneMgr, irr::f32 visionLength);

	/**
	 * Checks if the target is within the field of view and can be seen
	 */
	bool isObjectVisible(Detectable* object, irr::scene::ISceneManager* sceneMgr, irr::core::vector3df direction, irr::f32 visionLength);

	/** Virtual Methods that needs to be implemented **/

	/**
	 * Get the position of the object (node)
	 */
	virtual irr::core::vector3df getPosition() = 0;

	/**
	 * Get the ground position of the object (node)
	 */
	virtual irr::core::vector3df getGroundPosition() = 0;

	/**
	 * Get the rotation of the object (node)
	 */
	virtual irr::core::vector3df getRotation() = 0;

	/**
	 * Get the ID of the Node
	 */
	virtual irr::s32 getNodeID() = 0;

	/**
	 * Return the node
	 */
	virtual irr::scene::ISceneNode* getNode() = 0;
protected:
	// The length that defines how far this object can see
	irr::f32 visionLength;

	// The angle of the field of view in radians
	irr::f32 FOVRadian;
};