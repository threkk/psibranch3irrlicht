// Copyright (C) 2014 Alberto Martinez de Murga Ramirez
#ifndef __I_MESH_SCENE_LOADER_H_INCLUDED_
#define __I_MESH_SCENE_LOADER_H_INCLUDED_

#include "irrlicht.h"
#include "ISceneManager.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include "pthread.h"
//#include <pthread.h>

using namespace irr;
using namespace scene;

namespace irr
{
namespace scene
{
    /** TODO change this all comments

     * This class allows to load more scenes in addition to the current one to
     * the cache. The scenes are stored as .irr files and just providing the uri
     * all the resources are loaded to the cache. 
     *
     * Once the class is preloaded to the cache, you can change between the
     * current scene and any preloaded scene without having to load the
     * resources using the function setScene and giving the index returned
     * during the preloading. If one scene is not going to be used anymore, it
     * can be destroyed using dropPreloadedScene.
     *
     * For more information about the .irr files, read tutorial number 15.
     */

	class IRRLICHT_API ISceneMeshLoader 
	{
		/*#define SMGR_LOCK_START if(pthread_mutex_lock (&ISceneMeshLoader::mutexsum) == 0){
		#define SMGR_LOCK_END }pthread_mutex_unlock (&ISceneMeshLoader::mutexsum);*/

		struct threadArgs{
			scene::ISceneManager* smgr;
			scene::ISceneNode* node;
			io::path filePath;
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

		void switchSceneNode(ISceneNode* node, io::path filePath);

		static void startLock();
		static void endLock();
	};
} //! end namespace scene
} //! end namespace irr 
#endif
