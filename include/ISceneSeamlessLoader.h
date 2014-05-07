// Copyright (C) 2014 Alberto Martinez de Murga Ramirez
#ifndef __I_SEAMLESS_SCENE_LOADER_H_INCLUDED_
#define __I_SEAMLESS_SCENE_LOADER_H_INCLUDED_

#include "irrlicht.h"
#include "ISceneManager.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace irr;
using namespace scene;


namespace irr
{
namespace scene
{
    /**
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

	/**
     * Struct that contains all relevant information about a scene:
     * the position in the vector, the ISceneManager used to load the
     * resources and the uri to the file.
     */
	typedef struct {
		//! Position of the scene in the vector.
		int position;
        //! Scene manager used to load the resources. There is one different
        //! per scene. 
		ISceneManager* smngr;
        //! Uri to the .irr file.
		io::path uri;
	} NScene;

	class IRRLICHT_API ISceneSeamlessLoader 
	{
	private:
        //! Main scene manager that has the current scene.
		ISceneManager* actual;
        //! Vector with all the scenes preloaded.
		std::vector<NScene>* scenes;
		
	public:
        /**
         * Constructor.
         * \param smgr Actual scene manager. Usually, device->getSceneManager().
         */
		ISceneSeamlessLoader(ISceneManager* smgr);
        /**
         * Destructor. It drops all the scenes currently on the cache.
         */
		~ISceneSeamlessLoader();

        /**
         * This method adds one new scene to the vector and loads the resources
         * to the cache.
         * \param uriToNewScene The uri to the new scene to be added.
         * \return The NScene with its position in the vector in the position 
		 * field. Returns nothing in case of error.
         */
		NScene preloadScene(irr::io::path uriToNewScene);
        /**
         * This method unloads a scene from the cache. All the resources will be
         * dropped if they are not used by other scene.
         * \param sceneIndex Position in the vector to the scene to be unload.
         * \return true if dropped.
         */
		bool dropPreloadedScene(int sceneIndex);
        /**
         * This method switches from the current scene to a scene that is
         * already preloaded. The scene manager will not change but the scene
         * will be the new one.
         * \param sceneIndex Position in the vector of the scene.
         */
		void setScene(int sceneIndex);

		/**
		 * This method returns the vector with all the scenes currently preloaded.
		 * \return The vector with all the scenes currently loaded.
		 */
		std::vector<NScene> getScenes();
	};
} //! end namespace scene
} //! end namespace irr 
#endif
