// Copyright (C) 2014 Kevin van Mierlo
#ifndef __I_MESH_SCENE_LOADER_H_INCLUDED_
#define __I_MESH_SCENE_LOADER_H_INCLUDED_

#include "irrlicht.h"
#include "ISceneManager.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "pthread.h"
#include "ISceneMeshLoaderCallback.h"
#include <map>

using namespace irr;
using namespace scene;

namespace irr
{
namespace scene
{
    /**

     * This class allows you to load a new mesh asynchronous and via a callback method you can add the new mesh to your pointer.
	 * This class is used to make object appear better if you get closer to them (more polygons for example)
     */

	class IRRLICHT_API ISceneMeshLoader 
	{
		// Arguments for the thread
		struct threadArgs{
			scene::ISceneManager* smgr; //Scene manager that has the current scene
			scene::ISceneNode* node; // Scene node that will be replaced, used for location
			io::path filePath; // Filepath to where the new mesh is
			ISceneMeshLoaderCallback* callbackclass; // Callback for when everything is loaded
			int type; // Comes with the callback to check which mesh is loaded
		};

	private:
        // Main scene manager that has the current scene.
		ISceneManager* actual;

		// Hashmap to hold the low poly scenenodes
		static std::map<int, scene::ISceneNode*> unloadMap;

		/**
		 * Thread for loading new mesh
		 * \param threadargs. All the arguments casted as void* for the thread
		 */
		static void *loadNewFile(void *threadargs);
	public:
        /**
         * Constructor.
         * \param smgr Actual scene manager. Usually, device->getSceneManager().
         */
		ISceneMeshLoader(ISceneManager* smgr);
        /**
         * Destructor. destroys the mutex
         */
		~ISceneMeshLoader();

		/**
		 * Function to switch the scenenode. This function will call the thread with the available information
		 * \param node. The scene node that will be switched with another mesh.
		 * \param filePath. The path locating to the new mesh.
		 * \param callbackclass. Class which allows to send a callback with information.
		 * \param type. Comes with the callback to check which mesh is loaded.
		 */
		void switchSceneNode(ISceneNode* node, io::path filePath, ISceneMeshLoaderCallback* callbackclass, int type);

		/**
		 * Function to unload a scenenode. This function will remove the high poly scenenode and replace it for the old one
		 * \param node. High poly scenenode to be removed
		 * \param type. Type from scenenode (filled in at switchscenenode)
		 * \param callbackclass. Class which allows to send a callback with information
		 */
		void unloadSceneNode(ISceneNode* node, int type, ISceneMeshLoaderCallback* callbackclass);

		//Starts the lock to prevent simultaneously working with the same object.
		static void startLock();

		//Unlocks the lock when you're done.
		static void endLock();
	};
} //! end namespace scene
} //! end namespace irr 
#endif
