#include "ISceneSeamlessLoader.h"

//! Constructor
ISceneSeamlessLoader::ISceneSeamlessLoader(scene::ISceneManager* smgr) 
{
    //! Usually, device->getSceneManager()
	this->actual = smgr;
    //! Already initialized.
	this->scenes = new std::vector<NScene>();
}

//! Destructor
ISceneSeamlessLoader::~ISceneSeamlessLoader()
{
	//! First drop all the ISceneManager created.
	for(unsigned i = 0; i < this->scenes->size(); i++)
	{
		this->scenes->at(i).smngr->drop();
	}
	//! Clear the vector.
	this->scenes->clear();
	//! Delete everything.
	if(this->scenes) delete this->scenes;
}

//! Preload a scene to cache
NScene ISceneSeamlessLoader::preloadScene(io::path uriToNewScene) 
{
    //! Fill a new NScene.
	NScene scene;
	scene.uri = uriToNewScene;
	scene.smngr = actual->createNewSceneManager();
    //! It will be added at the end, so its index is the last one plus 1.
	scene.position = (int)scenes->size();

    //! Load .irr to cache.
	scene.smngr->loadScene(scene.uri);
	try
	{
    //! Add to the vector
	this->scenes->push_back(scene);
	}
    //! In case something goes wrong.
	catch(std::bad_alloc)
	{
		std::cout << "Allocation failed. The scene was not added.\n";
		return ;
	}
    //! Important. The position to call the scene.
	return scene;
}

//! Drops a scene. It works like the destructor but for only one scene.
bool ISceneSeamlessLoader::dropPreloadedScene(int sceneIndex)
{
	try 
	{
		NScene scene = this->scenes->at(sceneIndex);
		scene.smngr->drop();
		this->scenes->erase(this->scenes->begin() + sceneIndex);
		return true;
	} 
	catch(std::out_of_range)
	{
		std::cout << "Index out of bounds. The scene was not deleted\n";
		return false;
	}
}

//! Set the current scene to the new one. The manager won't change.
void ISceneSeamlessLoader::setScene(int sceneIndex)
{	
	try 
	{
		NScene scene = this->scenes->at(sceneIndex);
		actual->loadScene(scene.uri);
	} 
    // Case of error.
	catch(std::out_of_range)
	{
		std::cout << "Index out of bounds. The scene was not loaded\n";
		return ;
	}	
}

std::vector<NScene> ISceneSeamlessLoader::getScenes() 
{
	return *scenes;
}
