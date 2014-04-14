#include "ParticleModel.h"

using namespace irr;

/**
* Default constructor that creates a default particleModel
*/
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
////////////////////////// SETTERS ///////////////////////////////////
void ParticleModel::setEmitterType(EmitterTypes emitterType)
{
	this->emitterType = emitterType;
}

void ParticleModel::setAabbox(core::aabbox3df aabbox)
{
	this->aabbox = aabbox;
}

void ParticleModel::setDirection(core::vector3df direction)
{
	this->direction = direction;
}

void ParticleModel::setPosition(core::vector3df pos)
{
	this->position = pos;
}

void ParticleModel::setMaxAngleDegrees(s32 maxAngleDegrees)
{
	this->maxAngleDegrees = maxAngleDegrees;
}

void ParticleModel::setLifeTimeMax(u32 lifeTimeMax)
{
	this->lifeTimeMax = lifeTimeMax;
}

void ParticleModel::setLifeTimeMin(u32 lifeTimeMin)
{
	this->lifeTimeMin = lifeTimeMin;
}

void ParticleModel::setMaxPPS(u32 maxPPS)
{
	this->maxPPS = maxPPS;
}

void ParticleModel::setMinPPS(u32 minPPs)
{
	this->minPPS = minPPS;
}

void ParticleModel::setPathNameTexture(core::stringc pathNameTexture)
{
	this->pathNameTexture = pathNameTexture;
}

void ParticleModel::setMinColor(video::SColor color)
{
	this->minStartColor = color;
}

void ParticleModel::setMaxColor(video::SColor maxColor)
{
	this->maxStartColor = maxColor;
}

void ParticleModel::setMinStartSize(core::dimension2df minStartSize)
{
	this->minStartSize = minStartSize;
}

void ParticleModel::setMaxStartSize(core::dimension2df maxStartSize)
{
	this->maxStartSize = maxStartSize;
}



////////////////////////// GETTERS ///////////////////////////////////
ParticleModel::EmitterTypes ParticleModel::getEmitterType()
{
	return this->emitterType;
}

core::aabbox3df ParticleModel::getAabbox()
{
	return this->aabbox;
}

core::vector3df ParticleModel::getDirection()
{
	return this->direction;
}

core::vector3df ParticleModel::getPosition()
{
	return this->position;
}

s32 ParticleModel::getMaxAngleDegrees()
{
	return this->maxAngleDegrees;
}

u32 ParticleModel::getLifeTimeMax()
{
	return this->lifeTimeMax;
}

u32 ParticleModel::getLifeTimeMin()
{
	return this->lifeTimeMin;
}

u32 ParticleModel::getMaxPPS()
{
	return this->maxPPS;
}

u32 ParticleModel::getMinPPS()
{
	return this->minPPS;
}

core::stringc ParticleModel::getPathNameTexture()
{
	return this->pathNameTexture;
}

video::SColor ParticleModel::getMinStartColor()
{
	return this->minStartColor;
}

video::SColor ParticleModel::getMaxStartColor()
{
	return this->maxStartColor;
}

core::dimension2df ParticleModel::getMinStartSize()
{
	return this->minStartSize;
}

core::dimension2df ParticleModel::getMaxStartSize()
{
	return this->maxStartSize;
}


ParticleModel::~ParticleModel(void)
{
}

