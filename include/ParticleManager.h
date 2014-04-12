#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include <irrlicht.h>
#include "IrrCompileConfig.h"
#include "ParticleModel.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

class ParticleModel;

class IRRLICHT_API ParticleManager
{
	/**
	*	This class is used to control every particle that you would want to create. It contains two spawn functions: one that contains a particlemodel
	*	and one that contains the use of XML but this isn't implemented yet.
	*/
public:
	/**
	*	The constructor needs 3 parameters because these are used for creating a particle
	*/
	ParticleManager(video::IVideoDriver* driver, IrrlichtDevice* device, ISceneManager* smgr);

	/**
	*	This function returns a pointer to IParticleSystemSceneNode
	*	ParticleModel* model is an object that contains every attribute that is needed to create a particle
	*	Vector3df position is used for that position in the game world
	*	core::stringc pathName is used for the URL to the image that you want to use for the particle
	*/
	IParticleSystemSceneNode* spawnDataModelParticle(ParticleModel* model, vector3df position, core::stringc pathName);

	/**
	*	This function returns a pointer to IParticleSystemSceneNode
	*	core::stringc xmlName is an URL that contains every attribute that is needed to create a particle
	*	Vector3df position is used for that position in the game world
	*	core::stringc pathName is used for the URL to the image that you want to use for the particle
	*/
	IParticleSystemSceneNode* spawnXMLParticle(core::stringc xmlName, vector3df position);

	/**
	*	The deconstructor
	*/
	~ParticleManager(void);

	scene::ISceneManager* smgr;
	video::IVideoDriver* driver;
	IrrlichtDevice* device;

private:
	/**
	*	These functions are internally used inside the particleManager.cpp file to create the right emitter based on which particleModel
	*	is given as parameter during the spawnParticle functions.
	*/
	void createBoxEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createPointEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createAnimatedMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createCylinderEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createRingEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createSphereEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
};

#endif