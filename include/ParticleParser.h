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

};

#endif