#ifndef PARTICLEMODEL_H_
#define PARTICLEMODEL_H_

#include <irrlicht.h>
#include "IrrCompileConfig.h"

using namespace irr;

class IRRLICHT_API ParticleModel
{
	/**
	*	This class is used 
	*/
public:
	/**
	*	The default constructor
	*/
	ParticleModel();

	/**
	*	EmitterTypes are used to identify which emitter is needed to create in the ParticleManager class
	*/
	enum EmitterTypes
	{
		NONE = 0,
		BOX,
		POINT,
		ANIMATED_MESH,
		CYLINDER,
		MESH,
		RING,
		SPHERE
	};

	/**
	*	Setters for setting all the properties that are used for the particle
	*/
	void setEmitterType(EmitterTypes emitterType);
	void setAabbox(core::aabbox3df aabbox);
	void setDirection(core::vector3df direction);
	void setPosition(core::vector3df position);
	void setMaxAngleDegrees(s32 maxAngleDegrees);
	void setLifeTimeMax(u32 lifeTimeMax);
	void setLifeTimeMin(u32 lifeTimeMin);
	void setMaxPPS(u32 maxPPS);
	void setMinPPs(u32 minPPs);
	void setPathNameTexture(core::stringc pathNameTexture);
	void setMinColor(video::SColor minColor);
	void setMaxColor(video::SColor maxColor);
	void setMinStartSize(core::dimension2df minStartSize);
	void setMaxStartSize(core::dimension2df maxStartSize);

	/**
	*	Getters from all the properties
	*/
	EmitterTypes getEmitterType();
	core::aabbox3df getAabbox();
	core::vector3df getDirection();
	core::vector3df getPosition();
	s32 getMaxAngleDegrees();
	u32 getLifeTimeMax();
	u32 getlifeTimeMin();
	u32 getMaxPPS();
	u32 getMinPPS();
	core::stringc getPathNameTexture();
	video::SColor getMinStartColor();
	video::SColor getMaxStartColor();
	core::dimension2df getMinStartSize();
	core::dimension2df getMaxStartSize();
	
	/**
	*	Deconstructor
	*/
	~ParticleModel(void);

	/**
	*	the variables that are used for the particle
	*/
	//TO DO: set this to private and use setters in the mainscene.cpp
	EmitterTypes emitterType;
	core::aabbox3df aabbox;
	core::vector3df direction;
	core::vector3df position;
	s32 maxAngleDegrees;
	u32 lifeTimeMax,lifeTimeMin, maxPPS, minPPS;
	core::stringc pathNameTexture;
	video::SColor minStartColor, maxStartColor;
	core::dimension2df minStartSize, maxStartSize;

private:

};

#endif