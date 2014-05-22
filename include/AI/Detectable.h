#include <irrlicht.h>

#pragma once

/**
 * This abstract class should be inherited by objects that can be detected by other object.
 * It will be used for the requirements of different states.
 */
class __declspec(dllexport) Detectable
{
public:
	virtual ~Detectable(void);

	Detectable();
	Detectable(irr::f32 visionLengt, irr::f32 FOVRadian, irr::f32 meshSize);

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

	/**
	 * Checks if the object is in range of the length
	 */
	bool Detectable::isObjectClose(Detectable* object, irr::f32 visionLength);

	
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

	// The size of the mesh
	irr::f32 meshSize;
};