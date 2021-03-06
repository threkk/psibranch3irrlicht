#ifndef PARTICLEMANAGER_H_
#define PARTICLEMANAGER_H_

#include <irrlicht.h>
#include "IrrCompileConfig.h"
#include "ParticleModel.h"
#include "ParticleParser.h"
#include "TempEffect.h"

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

class ParticleModel;

class IRRLICHT_API ParticleManager
{
	/**
	*This class is used to control every particle that you would want to create. 
	*It contains two spawn functions: one that contains a particlemodel
	*and one that contains the use of XML but that isn't implemented yet.
	*/
public:
	/**
	*The constructor needs 3 parameters because these are used for creating a particle
	*/
	ParticleManager(video::IVideoDriver* driver, IrrlichtDevice* device, ISceneManager* smgr);

	/**
	*This function returns a pointer to IParticleSystemSceneNode.
	*ParticleModel* model is an object that contains every attribute
	*that is needed to create a particle.
	*Vector3df position is used for that position in the game world
	*core::stringc pathName is used for the URL to the image that
	*you want to use for the particle.
	*IAnimatedMesh* animatedMesh is used if you want to create an animated
	*mesh particle, but it isn't necessary.
	*IMesh* mesh is used if you want to create a mesh particle, but it isnt
	*necessary.
	*/
	IParticleSystemSceneNode* spawnDataModelParticle(ParticleModel* model, vector3df position, core::stringc pathName, IAnimatedMesh* animatedMesh = nullptr, IMesh* mesh = nullptr);

	/**
	*This function returns a pointer to IParticleSystemSceneNode
	*core::stringc xmlName is an URL to the path where the XML is
	*put into that contains every attribute that is needed to create a particle
	*Vector3df position is used for that position in the game world
	*core::stringc pathName is used for the URL to the image that
	*you want to use for the particle
	*IAnimatedMesh* animatedMesh is used if you want to create an animated
	*mesh particle, but it isn't necessary.
	*IMesh* mesh is used if you want to create a mesh particle, but it isnt
	*necessary.
	*/
	IParticleSystemSceneNode* spawnXMLParticle(const char* filename, vector3df position, IAnimatedMesh* animatedMesh = nullptr, IMesh* mesh = nullptr);

	/* Checks all the Temporary effects in the list tempEffects if
	they should stop emit or should be deleted. He always checks the size of the List first,
	because the value may not be lower then 1. If the tempEffect is deleted from the list
	he set the value tempEffect to -1 and continue with checking the next tempEffect. */
	void update(void);

	// Force to delete the Temporary Effects in the list tempEffects
	void clearTempEffects();

	/**
	*The deconstructor
	*/
	~ParticleManager(void);

	/**
	*Irrlicht stuff that is needed to create certain parts
	*that are used for the particles
	*/
	scene::ISceneManager* smgr;
	video::IVideoDriver* driver;
	IrrlichtDevice* device;

private:
	/**
	*These functions are internally used inside the particleManager.cpp file
	*to create the right emitter based on which particleModel
	*is given as parameter during the spawnParticle functions.
	*Without these functions there will be no particle visually visible
	*/
	void createBoxEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createPointEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createAnimatedMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode,IAnimatedMesh* mesh);
	void createCylinderEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createMeshEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode,IMesh* mesh);
	void createRingEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	void createSphereEmittingParticle(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);

	/**
	*This function checks if the particle uses an affector
	*an Affector is an external force acting on the particle like fadeout
	*/
	void checkForAffectors(ParticleModel* particleModel,IParticleSystemSceneNode* particleNode);
	
	// List to store the Temporary Effects
	core::list<TempEffect*> tempEffects;
};

#endif