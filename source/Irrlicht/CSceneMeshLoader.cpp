#include "ISceneMeshLoader.h"

std::map<int, scene::ISceneNode*> ISceneMeshLoader::unloadMap;

//mutex for locking
pthread_mutex_t mutexsum;

// Constructor
ISceneMeshLoader::ISceneMeshLoader(scene::ISceneManager* smgr) 
{
    // Usually, device->getSceneManager()
	this->actual = smgr;
}

// Switch the scenenode
void ISceneMeshLoader::switchSceneNode(ISceneNode* node, io::path filePath, ISceneMeshLoaderCallback* callbackclass, int type)
{
	//Fill the thread arguments
	threadArgs* args = new threadArgs();
	args->filePath = filePath;
	args->node = node;
	args->smgr = actual;
	args->callbackclass = callbackclass;
	args->type = type;
	
	//Initialize a thread
	pthread_t thread = pthread_t();
	//Initialize a mutex if necessary
	if(mutexsum == NULL)
		pthread_mutex_init(&mutexsum, NULL);
	int rc;
	//Create the thread with the arguments
	rc = pthread_create(&thread, NULL, loadNewFile, (void*)args);
	if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
	}
}

//Thread
void *ISceneMeshLoader::loadNewFile(void *threadargs)
{
	threadArgs* args = (threadArgs*) threadargs;
	//Create a new scenemanager so we don't interfere with the other one
	scene::ISceneManager* scenemgr = args->smgr->createNewSceneManager(false);

	//Get the new mesh from the filepath
	scene::IAnimatedMesh* aniMesh = scenemgr->getMesh(args->filePath);
	
	//Lock the part where you could interfere with the other scenemanager and scenenode
	pthread_mutex_lock(&mutexsum);
		scene::ISceneNode* newNode = args->smgr->addMeshSceneNode(aniMesh);
		newNode->setPosition(args->node->getPosition());
		//args->node->remove();
		unloadMap[args->type] = args->node;
		args->node->setVisible(false);
		//Callback with new scene node and type to check which mesh is loaded
		args->callbackclass->MeshCallBack(newNode, args->type);
	//Unlock the mutex because we won't interfere with the scenemanager anymore
    pthread_mutex_unlock(&mutexsum);
	
	//Clean up
	delete args;
	args = NULL;
    aniMesh = NULL;
	delete scenemgr;
	scenemgr = NULL;

	printf("threading done\n");

	return NULL;
}

//Unload scenenode
void ISceneMeshLoader::unloadSceneNode(ISceneNode* node, int type, ISceneMeshLoaderCallback* callbackclass)
{
	unloadMap[type]->setVisible(true);
	callbackclass->MeshCallBack(unloadMap[type], type);
	node->remove();
}

//Start a lock and if necessary initialize one
void ISceneMeshLoader::startLock()
{
	if(mutexsum == NULL)
		pthread_mutex_init(&mutexsum, NULL);

	pthread_mutex_lock(&mutexsum);
}

//Unlock the lock
void ISceneMeshLoader::endLock()
{
	pthread_mutex_unlock(&mutexsum);
}

//! Destructor
ISceneMeshLoader::~ISceneMeshLoader()
{
	pthread_mutex_destroy(&mutexsum);
}
