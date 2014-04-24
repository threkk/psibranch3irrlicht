#pragma once

#ifndef PARTICLEPARSER_H_
#define PARTICLEPARSER_H_

#include "irrlicht.h"
#include "ParticleModel.h"

using namespace irr;

class IRRLICHT_API ParticleParser
{

public:

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
	
	ParticleParser();
	~ParticleParser(void);

private:

	float dirX, dirY, dirZ; // floats to store the direction
	float minX, minY, minZ, maxX, maxY, maxZ; // floats to store the AABBOX
	float posX, posY, posZ; // Position
	float centerX, centerY, centerZ; // Center
	float normalX, normalY, normalZ; // Normal


	int emitterTypeINT;// int to store the emitter type
	EmitterTypes emitterType;
	s32 maxAngleAdegrees, mbNumber; // AngleDegrees
	u32 lifeTimeMin, lifeTimeMax, minPPS, maxPPS;// LifeTime
	s32 particlesPerSecond;// Particles Per Second
	video::SColor minStartColor, maxStartColor;
	core::dimension2df minStartSize, maxStartSize;
	core::stringc pathNameTexture;

};

#endif