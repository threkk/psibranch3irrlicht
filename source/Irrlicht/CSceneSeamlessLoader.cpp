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
/*
void loadthingies(){
	IMetaTriangleSelector * meta = this->next->createMetaTriangleSelector();
	core::array<scene::ISceneNode *> nodes;
		this->next->getSceneNodesFromType(scene::ESNT_ANY, nodes); // Find all nodes

		for (u32 i=0; i < nodes.size(); ++i)
		{
			scene::ISceneNode * node = nodes[i];
			scene::ITriangleSelector * selector = 0;

			switch(node->getType())
			{
			case scene::ESNT_CUBE:
			case scene::ESNT_ANIMATED_MESH:
				// Because the selector won't animate with the mesh,
				// and is only being used for camera collision, we'll just use an approximate
				// bounding box instead of ((scene::IAnimatedMeshSceneNode*)node)->getMesh(0)
				//selector = smgr->createTriangleSelector(((scene::IAnimatedMeshSceneNode*)node)->getMesh(),node);
				selector = actual->createTriangleSelectorFromBoundingBox(node);
			break;

			case scene::ESNT_MESH:
			case scene::ESNT_SPHERE: // Derived from IMeshSceneNode
				selector = actual->createTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
				break;

			case scene::ESNT_TERRAIN:
				selector = actual->createTerrainTriangleSelector((scene::ITerrainSceneNode*)node);
				break;

			case scene::ESNT_OCTREE:
				selector = actual->createOctreeTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
				break;

			default:
				// Don't create a selector for this node type
				break;
			}

			if(selector)
			{
				// Add it to the meta selector, which will take a reference to it
				meta->addTriangleSelector(selector);
				// And drop my reference to it, so that the meta selector owns it.
				selector->drop();
			}
	}

	meta->drop(); // I'm done with the meta selector now
}
*/