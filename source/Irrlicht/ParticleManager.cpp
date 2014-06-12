#include "ParticleManager.h"

ParticleManager::ParticleManager(video::IVideoDriver* videoDriver, IrrlichtDevice* irrDevice, ISceneManager* sManager)
{
	driver = videoDriver;
	device = irrDevice;
	smgr = sManager;
	tempEffects = core::list<TempEffect*>();
}

IParticleSystemSceneNode* ParticleManager::spawnDataModelParticle(ParticleModel* model, core::vector3df position, core::stringc pathName, IAnimatedMesh* animatedMesh, IMesh* mesh)
{
	IParticleSystemSceneNode* particleNode = smgr->addParticleSystemSceneNode(false);
	particleNode->setScale(core::vector3df(0.5f, 0.5f,0.5f));
	particleNode->setMaterialFlag(video::EMF_LIGHTING, false);
	particleNode->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);

	// Set the right matarial type for the particle node
	if (model->getMaterialType() == ParticleModel::MaterialTypes::ADD)
	{
		particleNode->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	}
	else if (model->getMaterialType() == ParticleModel::MaterialTypes::SOLID)
	{
		particleNode->setMaterialType(video::EMT_ONETEXTURE_BLEND);
		particleNode->getMaterial(0).MaterialTypeParam = video::pack_textureBlendFunc (video::EBF_SRC_ALPHA, video::EBF_ONE_MINUS_SRC_ALPHA,
			video::EMFN_MODULATE_1X, video::EAS_TEXTURE | video::EAS_VERTEX_COLOR);
	}

	// Set the particle texture
	particleNode->setMaterialTexture(0, driver->getTexture(pathName));

	// Set the node at the given position
	particleNode->setPosition(position);

	// Spawn an emitter based on the given type
	switch(model->getEmitterType())
	{
	case(model->BOX):
		this->createBoxEmittingParticle(model,particleNode);
		break;
	case(model->POINT):
		createPointEmittingParticle(model,particleNode);
		break;
	case(model->CYLINDER):
		createCylinderEmittingParticle(model,particleNode);
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

	// If the model has a value of stopEmitting or removeParticleAfter
	// then make a temporary particle effect and push it to the list tempEffects.
	if (model->getStopEmitting() > 0 || model->getRemoveParticleAfter() > 0)
	{
		TempEffect* temp = new TempEffect(particleNode, device->getTimer()->getTime(),
			model->getStopEmitting(), model->getRemoveParticleAfter());
		tempEffects.push_back(temp);
	}

	return particleNode;
}

IParticleSystemSceneNode* ParticleManager::spawnXMLParticle(const char* filename, vector3df position,IAnimatedMesh* animatedMesh, IMesh* mesh)
{
	// Parse the xml file to a particle model
	ParticleParser parser = ParticleParser();
	ParticleModel model = parser.parse(filename);

	// Spawn the particle model
	IParticleSystemSceneNode* particleNode = this->spawnDataModelParticle(&model, position, model.getPathNameTexture().c_str());

	// Return the particle node
	return particleNode;
}

void ParticleManager::createBoxEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	IParticleBoxEmitter* boxEmitter = particleNode->createBoxEmitter(particleModel->getAabbox(),particleModel->getDirection(),particleModel->getMinPPS(),
		particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),
		particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(boxEmitter);
	boxEmitter->drop();
	checkForAffectors(particleModel,particleNode);
}

void ParticleManager::createPointEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	IParticlePointEmitter* pointEmitter = particleNode->createPointEmitter(particleModel->getDirection(),particleModel->getMinPPS(),
		particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),
		particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(pointEmitter);
	pointEmitter->drop();
	checkForAffectors(particleModel,particleNode);
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
	checkForAffectors(particleModel,particleNode);
}

void ParticleManager::createCylinderEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	scene::IParticleCylinderEmitter* cylinderEmitter = particleNode->createCylinderEmitter(particleModel->getCenter(),particleModel->getRadius(),particleModel->getNormal(),
		particleModel->getLengthCylinder(),particleModel->getOutLineOnly(),particleModel->getDirection(),particleModel->getMinPPS(),particleModel->getMaxPPS(),
		particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),particleModel->getMaxAngleDegrees(),
		particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(cylinderEmitter);
	cylinderEmitter->drop();
	checkForAffectors(particleModel,particleNode);
}

void ParticleManager::createMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode, IMesh* mesh)
{
	scene::IParticleMeshEmitter* meshEmitter = particleNode->createMeshEmitter(mesh,particleModel->getUseNormalDirection(),particleModel->getDirection(),particleModel->getNormalDirectionModifier(),
		particleModel->getMbNumber(),particleModel->getEveryMeshVertex(),particleModel->getMinPPS(),particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),
		particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(meshEmitter);
	meshEmitter->drop();
	checkForAffectors(particleModel,particleNode);
}

void ParticleManager::createRingEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	scene::IParticleRingEmitter* ringEmitter = particleNode->createRingEmitter(particleModel->getCenter(),particleModel->getRadius(),particleModel->getRingThickness(),particleModel->getDirection(),
		particleModel->getMinPPS(),particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),
		particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(ringEmitter);
	ringEmitter->drop();
	checkForAffectors(particleModel,particleNode);
}

void ParticleManager::createSphereEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	scene::IParticleSphereEmitter* sphereEmitter = particleNode->createSphereEmitter(particleModel->getCenter(),particleModel->getRadius(),particleModel->getDirection(),
		particleModel->getMinPPS(),particleModel->getMaxPPS(),particleModel->getMinStartColor(),particleModel->getMaxStartColor(),particleModel->getLifeTimeMin(),particleModel->getLifeTimeMax(),
		particleModel->getMaxAngleDegrees(),particleModel->getMinStartSize(),particleModel->getMaxStartSize());
	particleNode->setEmitter(sphereEmitter);
	sphereEmitter->drop();
	checkForAffectors(particleModel,particleNode);
}

void ParticleManager::checkForAffectors(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode)
{
	for(auto affector = particleModel->getAffectors()->begin(); affector != particleModel->getAffectors()->end(); ++affector)
	{
		if ((*affector) == particleModel->ATTRACT)
		{
			scene::IParticleAffector* affector = particleNode->createAttractionAffector(particleModel->getAttractionAffectorPoint(),particleModel->getAttractionAffectorSpeed(),
				particleModel->getAttractionAffectorAttract(),particleModel->getAttractionAffectorAffectX(),particleModel->getAttractionAffectorAffectY(),particleModel->getAttractionAffectorAffectZ());
			particleNode->addAffector(affector);
			affector->drop();
		}
		else if((*affector) == particleModel->FADE_OUT)
		{
			scene::IParticleAffector* affector = particleNode->createFadeOutParticleAffector(particleModel->getFadeOutAffectorTargetColor(),
				particleModel->getFadeOutAffectorTimeNeededToFadeOut());
			particleNode->addAffector(affector);
			affector->drop();
		}
		else if((*affector) == particleModel->GRAVITY)
		{
			scene::IParticleAffector* affector = particleNode->createGravityAffector(particleModel->getGravityAffectorGravity(),particleModel->getGravityAffectorTimeForceLost());
			particleNode->addAffector(affector);
			affector->drop();
		}
		else if((*affector) == particleModel->ROTATE)
		{
			scene::IParticleAffector* affector = particleNode->createRotationAffector(particleModel->getRotationAffectorSpeed(),particleModel->getRotationAffectorPivotPoint());
			particleNode->addAffector(affector);
			affector->drop();
		}
		else if((*affector) == particleModel->SCALE)
		{
			scene::IParticleAffector* affector = particleNode->createScaleParticleAffector(particleModel->getScaleAffectorScaleTo());
			particleNode->addAffector(affector);
			affector->drop();
		}
	}
}

void ParticleManager::update()
{
	for(auto tempEffect = tempEffects.begin(); tempEffect != tempEffects.end(); ++tempEffect)
	{
		if ((*tempEffect)->isOver(device->getTimer()->getTime()))
		{
			if (tempEffect ==  tempEffects.begin()) {
				tempEffects.erase(tempEffect);
				tempEffect = tempEffects.begin();
				break;
			} else {
				core::list<TempEffect*>::Iterator current = tempEffect;
				tempEffect--;
				tempEffects.erase(current);
			}
		}
	}
}

void ParticleManager::clearTempEffects()
{
	tempEffects.clear();
}

ParticleManager::~ParticleManager(void)
{
}