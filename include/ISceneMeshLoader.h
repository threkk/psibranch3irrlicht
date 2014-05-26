// Copyright (C) 2014 Alberto Martinez de Murga Ramirez
#ifndef __I_MESH_SCENE_LOADER_H_INCLUDED_
#define __I_MESH_SCENE_LOADER_H_INCLUDED_

#include "irrlicht.h"
#include "ISceneManager.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "pthread.h"
#include "ISceneMeshLoaderCallback.h"
//#include <pthread.h>

using namespace irr;
using namespace scene;

namespace irr
{
namespace scene
{
    /**

     * This class allows you to load a new mesh asynchronous and via a callback method you can add the new mesh to your pointer.
	 * This class is used to make object appear better if you get closer to them (more polygons for example
     */

	class IRRLICHT_API ISceneMeshLoader 
	{
		struct threadArgs{
			scene::ISceneManager* smgr;
			scene::ISceneNode* node;
			io::path filePath;
			ISceneMeshLoaderCallback* callbackclass;
		};

	private:
        //! Main scene manager that has the current scene.
		ISceneManager* actual;

		static void *loadNewFile(void *threadargs);
	public:
        /**
         * Constructor.
         * \param smgr Actual scene manager. Usually, device->getSceneManager().
         */
		ISceneMeshLoader(ISceneManager* smgr);
        /**
         * Destructor. It drops all the scenes currently on the cache.
         */
		~ISceneMeshLoader();

		void switchSceneNode(ISceneNode* node, io::path filePath, ISceneMeshLoaderCallback* callbackclass);

		static void startLock();
		static void endLock();
	};
} //! end namespace scene
} //! end namespace irr 
#endif
