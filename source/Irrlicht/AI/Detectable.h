#include <irrlicht.h>

#pragma once

class Detectable
{
public:
	virtual ~Detectable(void);

	bool isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr, float visionLength);
	bool isObjectInfront(Detectable* object, irr::scene::ISceneManager* sceneMgr);
	bool isObjectVisible(Detectable* object, irr::scene::ISceneManager* sceneMgr);
	virtual irr::core::vector3df getPosition() = 0;
	virtual irr::core::vector3df getRotation() = 0;
	virtual irr::s32 getNodeID() = 0;
	virtual irr::scene::ISceneNode* getNode() = 0;
protected:
	irr::f32 visionLength;
	irr::f32 FOVRadian;
};


