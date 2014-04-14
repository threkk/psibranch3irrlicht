#include "ParticleManager.h"

ParticleManager::ParticleManager(video::IVideoDriver* videoDriver, IrrlichtDevice* irrDevice, ISceneManager* sManager)
{
	driver = videoDriver;
	device = irrDevice;
	smgr = sManager;
}

IParticleSystemSceneNode* ParticleManager::spawnDataModelParticle(ParticleModel* model, core::vector3df position, core::stringc pathName)
{
	IParticleSystemSceneNode* particleNode = smgr->addParticleSystemSceneNode(false);
	particleNode->setScale(core::vector3df(0.5f, 0.5f,0.5f));
	particleNode->setMaterialFlag(video::EMF_LIGHTING, false);
	particleNode->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
	particleNode->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	particleNode->setMaterialTexture(0, driver->getTexture(pathName));
	particleNode->setPosition(position);

	switch(model->getEmitterType())
	{
	case(model->BOX):
		this->createBoxEmittingParticle(model,particleNode);
		break;
	case(model->POINT):
		createPointEmittingParticle(model,particleNode);
		break;
	case(model->ANIMATED_MESH):
		createAnimatedMeshEmittingParticle(model,particleNode);
		break;
	case(model->CYLINDER):
		createCylinderEmittingParticle(model,particleNode);
		break;
	case(model->MESH):
		createMeshEmittingParticle(model,particleNode);
		break;
	case(model->RING):
		createRingEmittingParticle(model,particleNode);
		break;
	case(model->SPHERE):
		createSphereEmittingParticle(model,particleNode);
		break;
	case(model->NONE):
		break;
	}
	return particleNode;
}

IParticleSystemSceneNode* ParticleManager::spawnXMLParticle(core::stringc xmlName, vector3df position)
{
	IParticleSystemSceneNode* particleNode = smgr->addParticleSystemSceneNode(false);
	//TODO: when the parser is there this is the function that needs to be used instead of the dataModel
	return particleNode;
}

void ParticleManager::createBoxEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	IParticleBoxEmitter* boxEmitter = particleNode->createBoxEmitter(particleModel->getAabbox(),particleModel->getDirection(),particleModel->getMinPPS(),
		particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),particleModel->getMaxAngleDegrees(),
		particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(boxEmitter);
	boxEmitter->drop();
}

void ParticleManager::createPointEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	/*IParticlePointEmitter* pointEmitter = particleNode->createPointEmitter();
	particleNode->setEmitter(pointEmitter);
	pointEmitter->drop();*/
}

void ParticleManager::createAnimatedMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	/*scene::IParticleAnimatedMeshSceneNodeEmitter* animatedMeshEmitter = particleNode->createAnimatedMeshSceneNodeEmitter();
	particleNode->setEmitter(animatedMeshEmitter);
	animatedMeshEmitter->drop();*/
}

void ParticleManager::createCylinderEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	/*scene::IParticleCylinderEmitter* cylinderEmitter = particleNode->createCylinderEmitter();
	particleNode->setEmitter(cylinderEmitter);
	cylinderEmitter->drop();*/
}

void ParticleManager::createMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{

}

void ParticleManager::createRingEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{

}

void ParticleManager::createSphereEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{

}

ParticleManager::~ParticleManager(void)
{
}