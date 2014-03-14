#include "ISceneSeamlessLoader.h"

ISceneSeamlessLoader::ISceneSeamlessLoader(scene::ISceneManager* smgr) 
{
	this->actual = smgr;
	this->scenes = new std::vector<NScene>();
}

ISceneSeamlessLoader::~ISceneSeamlessLoader()
{
	// First drop all the ISceneManager created.
	for(unsigned i = 0; i < this->scenes->size(); i++)
	{
		this->scenes->at(i).smngr->drop();
	}
	// Clear the vector.
	this->scenes->clear();
	// Delete everything.
	if(this->scenes) delete this->scenes;
}

int ISceneSeamlessLoader::preloadScene(io::path uriToNewScene) 
{
	NScene scene;
	scene.uri = uriToNewScene;
	scene.smngr = actual->createNewSceneManager();
	scene.position = (int)scenes->size();

	scene.smngr->loadScene(scene.uri);
	try
	{
	this->scenes->push_back(scene);
	} 
	catch(std::bad_alloc)
	{
		std::cout << "Allocation failed. The scene was not added.\n";
		return -1;
	}
	return scene.position;
}

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

void ISceneSeamlessLoader::setScene(int sceneIndex)
{	
	try 
	{
		NScene scene = this->scenes->at(sceneIndex);
		actual->loadScene(scene.uri);
	} 
	catch(std::out_of_range)
	{
		std::cout << "Index out of bounds. The scene was not loaded\n";
		return ;
	}
}