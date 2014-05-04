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

void ParticleModel::setPosition(core::vector3df position)
{
	this->position = position;
}

void ParticleModel::setCenter(core::vector3df center)
{
	this->center = center;
}

void ParticleModel::setNormal(core::vector3df normal)
{
	this->normal = normal;
}

void ParticleModel::setMaxAngleDegrees(s32 maxAngleDegrees)
{
	this->maxAngleDegrees = maxAngleDegrees;
}

void ParticleModel::setMbNumber(s32 mbNumber)
{
	this->mbNumber = mbNumber;
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

void ParticleModel::setMinPPS(u32 minPPS)
{
	this->minPPS = minPPS;
}

void ParticleModel::setNormalDirectionModifier(f32 normalDirectionModifier)
{
	this->normalDirectionModifier = normalDirectionModifier;
}

void ParticleModel::setRadius(f32 radius)
{
	this->radius = radius;
}

void ParticleModel::setLengthCylinder(f32 lengthCylinder)
{
	this->lengthCylinder = lengthCylinder;
}

void ParticleModel::setRingThickness(f32 ringThickness)
{
	this->ringThickness = ringThickness;
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

void ParticleModel::setUseNormalDirection(bool useNormalDirection)
{
	this->useNormalDirection = useNormalDirection;
}

void ParticleModel::setEveryMeshVertex(bool everyMeshVertex)
{
	this->everyMeshVertex = everyMeshVertex;
}

void ParticleModel::setOutLineOnly(bool outlineOnly)
{
	this->outlineOnly = outlineOnly;
}

////////////////////////// AFFECTOR SETTERS ///////////////////////////////////
void ParticleModel::setAffectors(core::list<AffectorTypes> affectors)
{
	this->affectorTypes = affectors;
}

void ParticleModel::addAffectorType(AffectorTypes affectorType)
{
	this->affectorTypes.push_back(affectorType);
}

void ParticleModel::setAttractionAffectorPoint(core::vector3df point)
{
	this->point = point;
}

void ParticleModel::setAttractionAffectorSpeed(f32 speed)
{
	this->speed = speed;
}

void ParticleModel::setAttractionAffectorAttract(bool attract)
{
	this->attract = attract;
}

void ParticleModel::setAttractionAffectorAffectX(bool affectX)
{
	this->affectX = affectX;
}

void ParticleModel::setAttractionAffectorAffectY(bool affectY)
{
	this->affectY = affectY;
}

void ParticleModel::setAttractionAffectorAffectZ(bool affectZ)
{
	this->affectZ = affectZ;
}

void ParticleModel::setFadeOutAffectorTargetColor(video::SColor targetColor)
{
	this->targetColor = targetColor;
}

void ParticleModel::setFadeOutAffectorTimeNeededToFadeOut(u32 timeNeededToFadeOut)
{
	this->timeNeededToFadeOut = timeNeededToFadeOut;
}

void ParticleModel::setGravityAffectorGravity(core::vector3df gravity)
{
	this->gravity = gravity;
}

void ParticleModel::setGravityAffectorTimeForceLost(u32 timeForceLost)
{
	this->timeForceLost = timeForceLost;
}

void ParticleModel::setRotationAffectorSpeed(core::vector3df rotationSpeed)
{
	this->rotationSpeed = rotationSpeed;
}

void ParticleModel::setRotationAffectorPivotPoint(core::vector3df pivotPoint)
{
	this->pivotPoint = pivotPoint;
}

void ParticleModel::setScaleAffectorScaleTo(core::dimension2df scaleTo)
{
	this->scaleTo = scaleTo;
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

core::vector3df ParticleModel::getCenter()
{
	return this->center;
}

core::vector3df ParticleModel::getNormal()
{
	return this->normal;
}

s32 ParticleModel::getMaxAngleDegrees()
{
	return this->maxAngleDegrees;
}

s32 ParticleModel::getMbNumber()
{
	return this->mbNumber;
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

f32 ParticleModel::getNormalDirectionModifier()
{
	return this->normalDirectionModifier;
}

f32 ParticleModel::getRadius()
{
	return this->radius;
}

f32 ParticleModel::getLengthCylinder()
{
	return this->lengthCylinder;
}

f32 ParticleModel::getRingThickness()
{
	return this->ringThickness;
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

bool ParticleModel::getUseNormalDirection()
{
	return this->useNormalDirection;
}

bool ParticleModel::getEveryMeshVertex()
{
	return this->everyMeshVertex;
}

bool ParticleModel::getOutLineOnly()
{
	return this->outlineOnly;
}

////////////////////////// AFFECTOR GETTERS ///////////////////////////////////
core::list<ParticleModel::AffectorTypes>* ParticleModel::getAffectors()
{
	return &this->affectorTypes;
}

core::vector3df ParticleModel::getAttractionAffectorPoint()
{
	return this->point;
}

f32 ParticleModel::getAttractionAffectorSpeed()
{
	return this->speed;
}

bool ParticleModel::getAttractionAffectorAttract()
{
	return this->attract;
}

bool ParticleModel::getAttractionAffectorAffectX()
{
	return this->affectX;
}

bool ParticleModel::getAttractionAffectorAffectY()
{
	return this->affectY;
}

bool ParticleModel::getAttractionAffectorAffectZ()
{
	return this->affectZ;
}

video::SColor ParticleModel::getFadeOutAffectorTargetColor()
{
	return this->targetColor;
}

u32 ParticleModel::getFadeOutAffectorTimeNeededToFadeOut()
{
	return this->timeNeededToFadeOut;
}

core::vector3df ParticleModel::getGravityAffectorGravity()
{
	return this->gravity;
}

u32 ParticleModel::getGravityAffectorTimeForceLost()
{
	return this->timeForceLost;
}

core::vector3df ParticleModel::getRotationAffectorSpeed()
{
	return this->rotationSpeed;
}

core::vector3df ParticleModel::getRotationAffectorPivotPoint()
{
	return this->pivotPoint;
}

core::dimension2df ParticleModel::getScaleAffectorScaleTo()
{
	return this->scaleTo;
}

ParticleModel::~ParticleModel(void)
{
}

