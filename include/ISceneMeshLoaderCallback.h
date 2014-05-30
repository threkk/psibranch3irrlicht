#ifndef _INCLUDE_SCENE_MESH_LOADER_CALLBACK_H_
#define _INCLUDE_SCENE_MESH_LOADER_CALLBACK_H_
#include "irrlicht.h"

class ISceneMeshLoaderCallback {
public:
	virtual void MeshCallBack(irr::scene::ISceneNode* newnode, int type) = 0;

};

#endif;