#include "ParticleManager.h"

ParticleManager::ParticleManager(video::IVideoDriver* videoDriver, IrrlichtDevice* irrDevice, ISceneManager* sManager)
{
	driver = videoDriver;
	device = irrDevice;
	smgr = sManager;
}

IParticleSystemSceneNode* ParticleManager::spawnDataModelParticle(ParticleModel* model, core::vector3df position, core::stringc pathName,IAnimatedMesh* animatedMesh, IMesh* mesh)
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
		createAnimatedMeshEmittingParticle(model,particleNode,animatedMesh);
		break;
	case(model->CYLINDER):
		createCylinderEmittingParticle(model,particleNode);
		break;
	case(model->MESH):
		createMeshEmittingParticle(model,particleNode,mesh);
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

IParticleSystemSceneNode* ParticleManager::spawnXMLParticle(core::stringc xmlName, vector3df position,IAnimatedMesh* animatedMesh, IMesh* mesh)
{
	IParticleSystemSceneNode* particleNode = smgr->addParticleSystemSceneNode(false);
	//TODO: when the parser is there this is the function that needs to be used instead of the dataModel
	return particleNode;
}

void ParticleManager::createBoxEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	IParticleBoxEmitter* boxEmitter = particleNode->createBoxEmitter(particleModel->getAabbox(),particleModel->getDirection(),particleModel->getMinPPS(),
		particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),
		particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(boxEmitter);
	boxEmitter->drop();
	if(particleModel->getAffectorType() == particleModel->ATTRACT)
	{
		scene::IParticleAffector* affector = particleNode->createAttractionAffector(particleModel->getAttractionAffectorPoint(),particleModel->getAttractionAffectorSpeed(),
			particleModel->getAttractionAffectorAttract(),particleModel->getAttractionAffectorAffectX(),particleModel->getAttractionAffectorAffectY(),particleModel->getAttractionAffectorAffectZ());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->FADE_OUT)
	{
		scene::IParticleAffector* affector = particleNode->createFadeOutParticleAffector(particleModel->getFadeOutAffectorTargetColor(),
			particleModel->getFadeOutAffectorTimeNeededToFadeOut());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->GRAVITY)
	{
		scene::IParticleAffector* affector = particleNode->createGravityAffector(particleModel->getGravityAffectorGravity(),particleModel->getGravityAffectorTimeForceLost());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->ROTATE)
	{
		scene::IParticleAffector* affector = particleNode->createRotationAffector(particleModel->getRotationAffectorSpeed(),particleModel->getRotationAffectorPivotPoint());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->SCALE)
	{
		scene::IParticleAffector* affector = particleNode->createScaleParticleAffector(particleModel->getScaleAffectorScaleTo());
		particleNode->addAffector(affector);
		affector->drop();
	}
}

void ParticleManager::createPointEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	IParticlePointEmitter* pointEmitter = particleNode->createPointEmitter(particleModel->getDirection(),particleModel->getMinPPS(),
		particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),
		particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(pointEmitter);
	pointEmitter->drop();
	if(particleModel->getAffectorType() == particleModel->ATTRACT)
	{
		scene::IParticleAffector* affector = particleNode->createAttractionAffector(particleModel->getAttractionAffectorPoint(),particleModel->getAttractionAffectorSpeed(),
			particleModel->getAttractionAffectorAttract(),particleModel->getAttractionAffectorAffectX(),particleModel->getAttractionAffectorAffectY(),particleModel->getAttractionAffectorAffectZ());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->FADE_OUT)
	{
		scene::IParticleAffector* affector = particleNode->createFadeOutParticleAffector(particleModel->getFadeOutAffectorTargetColor(),
			particleModel->getFadeOutAffectorTimeNeededToFadeOut());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->GRAVITY)
	{
		scene::IParticleAffector* affector = particleNode->createGravityAffector(particleModel->getGravityAffectorGravity(),particleModel->getGravityAffectorTimeForceLost());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->ROTATE)
	{
		scene::IParticleAffector* affector = particleNode->createRotationAffector(particleModel->getRotationAffectorSpeed(),particleModel->getRotationAffectorPivotPoint());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->SCALE)
	{
		scene::IParticleAffector* affector = particleNode->createScaleParticleAffector(particleModel->getScaleAffectorScaleTo());
		particleNode->addAffector(affector);
		affector->drop();
	}
}

void ParticleManager::createAnimatedMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode,IAnimatedMesh* mesh)
{
	scene::IAnimatedMeshSceneNode* animatedMeshNode = smgr->addAnimatedMeshSceneNode(mesh,particleNode->getParent(),particleNode->getID(),particleNode->getPosition(),
		particleNode->getRotation(),particleNode->getScale(),false);
	scene::IParticleAnimatedMeshSceneNodeEmitter* animatedMeshEmitter = particleNode->createAnimatedMeshSceneNodeEmitter(animatedMeshNode,particleModel->getUseNormalDirection(),
		particleModel->getDirection(),particleModel->getNormalDirectionModifier(),particleModel->getMbNumber(),particleModel->getEveryMeshVertex(),particleModel->getMinPPS(),particleModel->getMaxPPS(),
		particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),particleModel->getMaxAngleDegrees(),
		particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(animatedMeshEmitter);
	animatedMeshEmitter->drop();
	if(particleModel->getAffectorType() == particleModel->ATTRACT)
	{
		scene::IParticleAffector* affector = particleNode->createAttractionAffector(particleModel->getAttractionAffectorPoint(),particleModel->getAttractionAffectorSpeed(),
			particleModel->getAttractionAffectorAttract(),particleModel->getAttractionAffectorAffectX(),particleModel->getAttractionAffectorAffectY(),particleModel->getAttractionAffectorAffectZ());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->FADE_OUT)
	{
		scene::IParticleAffector* affector = particleNode->createFadeOutParticleAffector(particleModel->getFadeOutAffectorTargetColor(),
			particleModel->getFadeOutAffectorTimeNeededToFadeOut());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->GRAVITY)
	{
		scene::IParticleAffector* affector = particleNode->createGravityAffector(particleModel->getGravityAffectorGravity(),particleModel->getGravityAffectorTimeForceLost());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->ROTATE)
	{
		scene::IParticleAffector* affector = particleNode->createRotationAffector(particleModel->getRotationAffectorSpeed(),particleModel->getRotationAffectorPivotPoint());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->SCALE)
	{
		scene::IParticleAffector* affector = particleNode->createScaleParticleAffector(particleModel->getScaleAffectorScaleTo());
		particleNode->addAffector(affector);
		affector->drop();
	}
}

void ParticleManager::createCylinderEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	scene::IParticleCylinderEmitter* cylinderEmitter = particleNode->createCylinderEmitter(particleModel->getCenter(),particleModel->getRadius(),particleModel->getNormal(),
		particleModel->getLengthCylinder(),particleModel->getOutLineOnly(),particleModel->getDirection(),particleModel->getMinPPS(),particleModel->getMaxPPS(),
		particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),particleModel->getMaxAngleDegrees(),
		particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(cylinderEmitter);
	cylinderEmitter->drop();
	if(particleModel->getAffectorType() == particleModel->ATTRACT)
	{
		scene::IParticleAffector* affector = particleNode->createAttractionAffector(particleModel->getAttractionAffectorPoint(),particleModel->getAttractionAffectorSpeed(),
			particleModel->getAttractionAffectorAttract(),particleModel->getAttractionAffectorAffectX(),particleModel->getAttractionAffectorAffectY(),particleModel->getAttractionAffectorAffectZ());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->FADE_OUT)
	{
		scene::IParticleAffector* affector = particleNode->createFadeOutParticleAffector(particleModel->getFadeOutAffectorTargetColor(),
			particleModel->getFadeOutAffectorTimeNeededToFadeOut());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->GRAVITY)
	{
		scene::IParticleAffector* affector = particleNode->createGravityAffector(particleModel->getGravityAffectorGravity(),particleModel->getGravityAffectorTimeForceLost());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->ROTATE)
	{
		scene::IParticleAffector* affector = particleNode->createRotationAffector(particleModel->getRotationAffectorSpeed(),particleModel->getRotationAffectorPivotPoint());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->SCALE)
	{
		scene::IParticleAffector* affector = particleNode->createScaleParticleAffector(particleModel->getScaleAffectorScaleTo());
		particleNode->addAffector(affector);
		affector->drop();
	}
}

void ParticleManager::createMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode, IMesh* mesh)
{
	scene::IParticleMeshEmitter* meshEmitter = particleNode->createMeshEmitter(mesh,particleModel->getUseNormalDirection(),particleModel->getDirection(),particleModel->getNormalDirectionModifier(),
		particleModel->getMbNumber(),particleModel->getEveryMeshVertex(),particleModel->getMinPPS(),particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),
		particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(meshEmitter);
	meshEmitter->drop();
	if(particleModel->getAffectorType() == particleModel->ATTRACT)
	{
		scene::IParticleAffector* affector = particleNode->createAttractionAffector(particleModel->getAttractionAffectorPoint(),particleModel->getAttractionAffectorSpeed(),
			particleModel->getAttractionAffectorAttract(),particleModel->getAttractionAffectorAffectX(),particleModel->getAttractionAffectorAffectY(),particleModel->getAttractionAffectorAffectZ());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->FADE_OUT)
	{
		scene::IParticleAffector* affector = particleNode->createFadeOutParticleAffector(particleModel->getFadeOutAffectorTargetColor(),
			particleModel->getFadeOutAffectorTimeNeededToFadeOut());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->GRAVITY)
	{
		scene::IParticleAffector* affector = particleNode->createGravityAffector(particleModel->getGravityAffectorGravity(),particleModel->getGravityAffectorTimeForceLost());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->ROTATE)
	{
		scene::IParticleAffector* affector = particleNode->createRotationAffector(particleModel->getRotationAffectorSpeed(),particleModel->getRotationAffectorPivotPoint());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->SCALE)
	{
		scene::IParticleAffector* affector = particleNode->createScaleParticleAffector(particleModel->getScaleAffectorScaleTo());
		particleNode->addAffector(affector);
		affector->drop();
	}
}

void ParticleManager::createRingEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	scene::IParticleRingEmitter* ringEmitter = particleNode->createRingEmitter(particleModel->getCenter(),particleModel->getRadius(),particleModel->getRingThickness(),particleModel->getDirection(),
		particleModel->getMinPPS(),particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),
		particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(ringEmitter);
	ringEmitter->drop();
	if(particleModel->getAffectorType() == particleModel->ATTRACT)
	{
		scene::IParticleAffector* affector = particleNode->createAttractionAffector(particleModel->getAttractionAffectorPoint(),particleModel->getAttractionAffectorSpeed(),
			particleModel->getAttractionAffectorAttract(),particleModel->getAttractionAffectorAffectX(),particleModel->getAttractionAffectorAffectY(),particleModel->getAttractionAffectorAffectZ());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->FADE_OUT)
	{
		scene::IParticleAffector* affector = particleNode->createFadeOutParticleAffector(particleModel->getFadeOutAffectorTargetColor(),
			particleModel->getFadeOutAffectorTimeNeededToFadeOut());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->GRAVITY)
	{
		scene::IParticleAffector* affector = particleNode->createGravityAffector(particleModel->getGravityAffectorGravity(),particleModel->getGravityAffectorTimeForceLost());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->ROTATE)
	{
		scene::IParticleAffector* affector = particleNode->createRotationAffector(particleModel->getRotationAffectorSpeed(),particleModel->getRotationAffectorPivotPoint());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->SCALE)
	{
		scene::IParticleAffector* affector = particleNode->createScaleParticleAffector(particleModel->getScaleAffectorScaleTo());
		particleNode->addAffector(affector);
		affector->drop();
	}
}

void ParticleManager::createSphereEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	scene::IParticleSphereEmitter* sphereEmitter = particleNode->createSphereEmitter(particleModel->getCenter(),particleModel->getRadius(),particleModel->getDirection(),
		particleModel->getMinPPS(),particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),
		particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(sphereEmitter);
	sphereEmitter->drop();
	if(particleModel->getAffectorType() == particleModel->ATTRACT)
	{
		scene::IParticleAffector* affector = particleNode->createAttractionAffector(particleModel->getAttractionAffectorPoint(),particleModel->getAttractionAffectorSpeed(),
			particleModel->getAttractionAffectorAttract(),particleModel->getAttractionAffectorAffectX(),particleModel->getAttractionAffectorAffectY(),particleModel->getAttractionAffectorAffectZ());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->FADE_OUT)
	{
		scene::IParticleAffector* affector = particleNode->createFadeOutParticleAffector(particleModel->getFadeOutAffectorTargetColor(),
			particleModel->getFadeOutAffectorTimeNeededToFadeOut());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->GRAVITY)
	{
		scene::IParticleAffector* affector = particleNode->createGravityAffector(particleModel->getGravityAffectorGravity(),particleModel->getGravityAffectorTimeForceLost());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->ROTATE)
	{
		scene::IParticleAffector* affector = particleNode->createRotationAffector(particleModel->getRotationAffectorSpeed(),particleModel->getRotationAffectorPivotPoint());
		particleNode->addAffector(affector);
		affector->drop();
	}
	else if(particleModel->getAffectorType() == particleModel->SCALE)
	{
		scene::IParticleAffector* affector = particleNode->createScaleParticleAffector(particleModel->getScaleAffectorScaleTo());
		particleNode->addAffector(affector);
		affector->drop();
	}
}

ParticleManager::~ParticleManager(void)
{
}