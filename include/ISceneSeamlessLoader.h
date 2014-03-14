#ifndef __I_SEAMLESS_SCENE_LOADER_H_INCLUDED_
#define __I_SEAMLESS_SCENE_LOADER_H_INCLUDED_

#include "irrlicht.h"
#include "ISceneManager.h"
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace irr;
using namespace scene;

namespace irr {
namespace scene 
{
	class ISceneSeamlessLoader 
	{
	private: 
		typedef struct {
			int position;
			ISceneManager* smngr;
			io::path uri;
		} NScene;

		ISceneManager* actual;
		std::vector<NScene>* scenes;
		
	public:
		ISceneSeamlessLoader(ISceneManager* smgr);
		~ISceneSeamlessLoader();

		virtual int preloadScene(irr::io::path uriToNewScene);
		virtual bool dropPreloadedScene(int sceneIndex);
		virtual void setScene(int sceneIndex);
	};
}
}
#endif