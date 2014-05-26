#include "ISceneMeshLoader.h"

pthread_mutex_t mutexsum;

//! Constructor
ISceneMeshLoader::ISceneMeshLoader(scene::ISceneManager* smgr) 
{
    //! Usually, device->getSceneManager()
	this->actual = smgr;
}

void ISceneMeshLoader::switchSceneNode(ISceneNode* node, io::path filePath, ISceneMeshLoaderCallback* callbackclass)
{
	threadArgs* args = new threadArgs();
	args->filePath = filePath;
	args->node = node;
	args->smgr = actual;
	args->callbackclass = callbackclass;
	pthread_t thread = pthread_t();
	if(mutexsum == NULL)
		pthread_mutex_init(&mutexsum, NULL);
	int rc;
	rc = pthread_create(&thread, NULL, loadNewFile, (void*)args);
	if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
	}
}

void *ISceneMeshLoader::loadNewFile(void *threadargs)
{
	threadArgs* args = (threadArgs*) threadargs;
	scene::ISceneManager* scenemgr = args->smgr->createNewSceneManager(false);

	scene::IAnimatedMesh* aniMesh = scenemgr->getMesh(args->filePath);//"../media/2.irrmesh");
	
	pthread_mutex_lock(&mutexsum);
		scene::ISceneNode* newNode = args->smgr->addMeshSceneNode(aniMesh);
		newNode->setPosition(args->node->getPosition());
//		args->smgr->getRootSceneNode()->removeChild(args->node);
		//scene::ISceneNode *test = args->node->;
		//*test = *args->node;
		args->node->remove();
		//*args->node = *newNode;
		//newNode = NULL;
		//test->remove();
		args->callbackclass->MeshCallBack(newNode);
    pthread_mutex_unlock(&mutexsum);
	
	delete args;
	args = NULL;
    aniMesh = NULL;
	delete scenemgr;
	scenemgr = NULL;

	printf("threading done\n");

	return NULL;
}

void ISceneMeshLoader::startLock()
{
	if(mutexsum == NULL)
		pthread_mutex_init(&mutexsum, NULL);

	pthread_mutex_lock(&mutexsum);
}

void ISceneMeshLoader::endLock()
{
	pthread_mutex_unlock(&mutexsum);
}

//! Destructor
ISceneMeshLoader::~ISceneMeshLoader()
{
	pthread_mutex_destroy(&mutexsum);
}
