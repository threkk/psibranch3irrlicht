#ifndef PARTICLEMODEL_H_
#define PARTICLEMODEL_H_

#include <irrlicht.h>
#include "IrrCompileConfig.h"

using namespace irr;

class IRRLICHT_API ParticleModel
{
	/**
	 * This class is used to store every attribute that is needed to create a particle.
	 * You can store them manually by setting every property
	 * Or you can use the xml that is created from the editor
	 * to get all the attributes that are stored into that xml and put it into
	 * this particlemodel.
	 */
public:
	/**
	 * The default constructor
	 */
	ParticleModel();

	/**
	 * EmitterTypes are used to identify which emitter
	 * is needed to create in the ParticleManager class
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
	 * AffectorTypes are used to identify which affector
	 * is added to a particle this is used to
	 * create the affector in the ParticleManager class
	 */
	enum AffectorTypes
	{
		NOPE = 0,
		ATTRACT,
		FADE_OUT,
		GRAVITY,
		ROTATE,
		SCALE
	};

	/**
	 * Setters for setting all the properties that are used for the particle emitters
	 */
	void setEmitterType(EmitterTypes emitterType);
	void setAabbox(core::aabbox3df aabbox);
	void setDirection(core::vector3df direction);
	void setPosition(core::vector3df position);
	void setCenter(core::vector3df center);
	void setNormal(core::vector3df normal);
	void setMaxAngleDegrees(s32 maxAngleDegrees);
	void setMbNumber(s32 mbNumber);
	void setLifeTimeMax(u32 lifeTimeMax);
	void setLifeTimeMin(u32 lifeTimeMin);
	void setMaxPPS(u32 maxPPS);
	void setMinPPS(u32 minPPS);
	void setNormalDirectionModifier(f32 normalDirectionModifier);
	void setRadius(f32 radius);
	void setLengthCylinder(f32 lengthCylinder);
	void setRingThickness(f32 ringThickness);
	void setPathNameTexture(core::stringc pathNameTexture);
	void setMinColor(video::SColor minColor);
	void setMaxColor(video::SColor maxColor);
	void setMinStartSize(core::dimension2df minStartSize);
	void setMaxStartSize(core::dimension2df maxStartSize);
	void setUseNormalDirection(bool useNormalDirection);
	void setEveryMeshVertex(bool everMeshVertex);
	void setOutLineOnly(bool outlineOnly);

	/**
	 * Setters for setting all the properties that are used for the particle affectors
	 */
	void setAffectors(core::list<AffectorTypes> affectors);
	void addAffectorType(AffectorTypes affectorType);
	void setAttractionAffectorPoint(core::vector3df point);
	void setAttractionAffectorSpeed(f32 speed);
	void setAttractionAffectorAttract(bool attract);
	void setAttractionAffectorAffectX(bool affectX);
	void setAttractionAffectorAffectY(bool affectY);
	void setAttractionAffectorAffectZ(bool affectZ);
	void setFadeOutAffectorTargetColor(video::SColor targetColor);
	void setFadeOutAffectorTimeNeededToFadeOut(u32 timeNeededToFadeOut);
	void setGravityAffectorGravity(core::vector3df gravity);
	void setGravityAffectorTimeForceLost(u32 timeForceLost);
	void setRotationAffectorSpeed(core::vector3df rotationSpeed);
	void setRotationAffectorPivotPoint(core::vector3df pivotPoint);
	void setScaleAffectorScaleTo(core::dimension2df scaleTo);

	/**
	 * Getters from all the properties for the emitters
	 */
	EmitterTypes getEmitterType();
	core::aabbox3df getAabbox();
	core::vector3df getDirection();
	core::vector3df getPosition();
	core::vector3df getCenter();
	core::vector3df getNormal();
	s32 getMaxAngleDegrees();
	s32 getMbNumber();
	u32 getLifeTimeMax();
	u32 getLifeTimeMin();
	u32 getMaxPPS();
	u32 getMinPPS();
	f32 getNormalDirectionModifier();
	f32 getRadius();
	f32 getLengthCylinder();
	f32 getRingThickness();
	core::stringc getPathNameTexture();
	video::SColor getMinStartColor();
	video::SColor getMaxStartColor();
	core::dimension2df getMinStartSize();
	core::dimension2df getMaxStartSize();
	bool getUseNormalDirection();
	bool getEveryMeshVertex();
	bool getOutLineOnly();

	/**
	 * Getters from all the properties for the affectors
	 */
	core::list<AffectorTypes>* getAffectors();
	core::vector3df getAttractionAffectorPoint();
	f32 getAttractionAffectorSpeed();
	bool getAttractionAffectorAttract();
	bool getAttractionAffectorAffectX();
	bool getAttractionAffectorAffectY();
	bool getAttractionAffectorAffectZ();
	video::SColor getFadeOutAffectorTargetColor();
	u32 getFadeOutAffectorTimeNeededToFadeOut();
	core::vector3df getGravityAffectorGravity();
	u32 getGravityAffectorTimeForceLost();
	core::vector3df getRotationAffectorSpeed();
	core::vector3df getRotationAffectorPivotPoint();
	core::dimension2df getScaleAffectorScaleTo();

	void print(void);

	/**
	 * Deconstructor
	 */
	~ParticleModel(void);

private:

	/**
	 * The variables that are used for the particle emitter
	 */
	EmitterTypes emitterType;
	core::aabbox3df aabbox;
	core::vector3df position,direction,center,normal;
	s32 maxAngleDegrees, mbNumber;
	u32 lifeTimeMax,lifeTimeMin, maxPPS, minPPS;
	f32 normalDirectionModifier, radius, lengthCylinder, ringThickness;
	core::stringc pathNameTexture;
	video::SColor minStartColor, maxStartColor;
	core::dimension2df minStartSize, maxStartSize;
	bool useNormalDirection, everyMeshVertex, outlineOnly;

	/**
	 * The variables that are used for the particle affector
	 */
	core::list<AffectorTypes> affectorTypes;
	core::vector3df point, gravity, rotationSpeed, pivotPoint;
	f32 speed;
	bool attract, affectX, affectY, affectZ;
	video::SColor targetColor;
	u32 timeNeededToFadeOut, timeForceLost;
	core::dimension2df scaleTo;
};

#endif
