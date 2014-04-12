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
	lifeTimeMin = 50;
	lifeTimeMax = 75;
	maxAngleDegrees = 0;
	minStartSize = core::dimension2df(4.0f, 4.0f);
	maxStartSize = core ::dimension2df(8.0f, 8.0f);
	position = core::vector3df(0,0,0);
	pathNameTexture;
}

void ParticleModel::setMinColor(video::SColor color)
{
	this->minStartColor = color;
}

void ParticleModel::setPosition(core::vector3df pos)
{
	this->position = pos;
}

video::SColor ParticleModel::getMinStartColor()
{
	return minStartColor;
}

core::vector3df ParticleModel::getPosition()
{
	return position;
}

ParticleModel::~ParticleModel(void)
{
}

