#ifndef PARTICLEMODEL_H_
#define PARTICLEMODEL_H_

#include <irrlicht.h>
#include "IrrCompileConfig.h"

using namespace irr;

class IRRLICHT_API ParticleModel
{
public:
	ParticleModel();
	void setMinColor(video::SColor color);
	void setPosition(core::vector3df pos);
	video::SColor getminStartColor();
	~ParticleModel(void);

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