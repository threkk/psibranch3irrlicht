#include "ParticleModel.h"

using namespace irr;

ParticleModel::ParticleModel()
{
	emitterType = BOX;
	aabbox = core::aabbox3df(-3, 0, -3, 3, 1, 3 );
	direction = core::vector3df(0.0f, 0.1f, 0.0f);
	minPPS = 50;
	maxPPS = 200;
	minStartColor = video::SColor(0,0,0,255);
	maxStartColor = video::SColor(0,255,255,255);
	lifeTimeMin = 500;
	lifeTimeMax = 750;
	maxAngleDegrees = 0;
	minStartSize = core::dimension2df(4.0f, 4.0f);
	maxStartSize = core ::dimension2df(8.0f, 8.0f);
	pathNameTexture;
}

void ParticleModel::setMinColor(video::SColor color)
{
	this->minStartColor = color;
}

video::SColor ParticleModel::getminStartColor()
{
	return minStartColor;
}

ParticleModel::~ParticleModel(void)
{
}

