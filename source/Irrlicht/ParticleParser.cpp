#include "ParticleParser.h"

using namespace irr;

ParticleParser::ParticleParser()
{

}

ParticleModel ParticleParser::parse(const char* filename)
{
	// Creates a XML reader and set path to load the XML file from
	io::IrrXMLReader* xmlReader = io::createIrrXMLReader(filename);

	// The Particle model where all the values will be stored
	ParticleModel model = ParticleModel();

	while (xmlReader && xmlReader->read())
	{
		switch (xmlReader->getNodeType())
		{
		// Search for elements in the XML file and store them in the model
		case io::EXN_ELEMENT:
			{
				// Particle attributes
				if (!strcmp("Direction", xmlReader->getNodeName()))
				{
					model.setDirection(core::vector3df(xmlReader->getAttributeValueAsFloat("X"),
						xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));
				}
				else if (!strcmp("Emitter", xmlReader->getNodeName()))
				{
					model.setEmitterType(ParticleModel::EmitterTypes(xmlReader->getAttributeValueAsInt("Type")));
				}
				else if (!strcmp("Aabbox", xmlReader->getNodeName()))
				{
					model.setAabbox(core::aabbox3df(xmlReader->getAttributeValueAsFloat("MinX"), xmlReader->getAttributeValueAsFloat("MinY"),
						xmlReader->getAttributeValueAsFloat("MinZ"), xmlReader->getAttributeValueAsFloat("MaxX"),
						xmlReader->getAttributeValueAsFloat("MaxY"), xmlReader->getAttributeValueAsFloat("MaxZ")));
				}
				else if (!strcmp("Position", xmlReader->getNodeName()))
				{
					model.setPosition(core::vector3df(xmlReader->getAttributeValueAsFloat("X"),
					xmlReader->getAttributeValueAsFloat("Y"), xmlReader->getAttributeValueAsFloat("Z")));
				}
				else if (!strcmp("Center", xmlReader->getNodeName()))
				{
					model.setCenter(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));
				}
				else if (!strcmp("Normal", xmlReader->getNodeName()))
				{
					model.setNormal(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));
				}
				else if (!strcmp("AngleDegrees", xmlReader->getNodeName()))
				{
					model.setMaxAngleDegrees(s32(xmlReader->getAttributeValueAsInt("Max")));
				}
				else if (!strcmp("LifeTime", xmlReader->getNodeName()))
				{
					model.setLifeTimeMax(u32(xmlReader->getAttributeValueAsInt("Max")));
					model.setLifeTimeMin(u32(xmlReader->getAttributeValueAsInt("Min")));
				}
				else if (!strcmp("PPS", xmlReader->getNodeName()))
				{
					model.setMaxPPS(u32(xmlReader->getAttributeValueAsInt("Max")));
					model.setMinPPS(u32(xmlReader->getAttributeValueAsInt("Min")));
				}
				else if (!strcmp("MaxStartColor", xmlReader->getNodeName()))
				{
					model.setMaxColor(video::SColor(xmlReader->getAttributeValueAsInt("Alpha"), xmlReader->getAttributeValueAsInt("Red"),
						xmlReader->getAttributeValueAsInt("Green"), xmlReader->getAttributeValueAsInt("Blue")));
				}
				else if (!strcmp("MinStartColor", xmlReader->getNodeName()))
				{
					model.setMinColor(video::SColor(xmlReader->getAttributeValueAsInt("Alpha"), xmlReader->getAttributeValueAsInt("Red"),
						xmlReader->getAttributeValueAsInt("Green"), xmlReader->getAttributeValueAsInt("Blue")));
				}
				else if (!strcmp("MaxStartSize", xmlReader->getNodeName()))
				{
					model.setMaxStartSize(core::dimension2df(xmlReader->getAttributeValueAsFloat("Width"), xmlReader->getAttributeValueAsFloat("Height")));
				}
				else if (!strcmp("MinStartSize", xmlReader->getNodeName()))
				{
					model.setMinStartSize(core::dimension2df(xmlReader->getAttributeValueAsFloat("Width"), xmlReader->getAttributeValueAsFloat("Height")));
				}
				else if (!strcmp("Texture", xmlReader->getNodeName()))
				{
					core::stringc filepath = core::stringc(filename);
					filepath = filepath.subString(0, filepath.findLastChar("/"));
					core::stringc text = core::stringc(xmlReader->getAttributeValue("PathName"));
					model.setPathNameTexture(filepath + "/" + text);
				}
				else if (!strcmp("Material", xmlReader->getNodeName()))
				{
					model.setMaterialType(ParticleModel::MaterialTypes(xmlReader->getAttributeValueAsInt("Type")));
				}
				else if (!strcmp("Rest", xmlReader->getNodeName()))
				{
					model.setOutLineOnly(s32(xmlReader->getAttributeValueAsInt("OutLineOnly")));
					model.setEveryMeshVertex(s32(xmlReader->getAttributeValueAsInt("EveryMeshVertex")));
					model.setUseNormalDirection(s32(xmlReader->getAttributeValueAsInt("UseNormalDirection")));
					model.setRingThickness(f32(xmlReader->getAttributeValueAsFloat("RingThickness")));
					model.setLengthCylinder(f32(xmlReader->getAttributeValueAsFloat("LengthCylinder")));
					model.setRadius(f32(xmlReader->getAttributeValueAsFloat("Radius")));
					model.setNormalDirectionModifier(f32(xmlReader->getAttributeValueAsFloat("NormalDirectionModifier")));
					model.setMbNumber(s32(xmlReader->getAttributeValueAsInt("MbNumber")));
				}
				else if (!strcmp("StopEmitting", xmlReader->getNodeName()))
				{
					model.setStopEmitting(u32(xmlReader->getAttributeValueAsInt("StopEmittingAfter")));
				}
				else if (!strcmp("RemoveParticleAfter", xmlReader->getNodeName()))
				{
					model.setRemoveParticleAfter(u32(xmlReader->getAttributeValueAsInt("RemoveParticleAfter")));
				}

				// Affectors
				else if (!strcmp("FadeOutAffectorTargetColor", xmlReader->getNodeName()))
				{
					model.setFadeOutAffectorTargetColor(video::SColor(xmlReader->getAttributeValueAsInt("Alpha"), xmlReader->getAttributeValueAsInt("Red"),
						xmlReader->getAttributeValueAsInt("Green"), xmlReader->getAttributeValueAsInt("Blue")));
				}
				else if (!strcmp("FADE_OUT_Rest", xmlReader->getNodeName()))
				{
					model.setFadeOutAffectorTimeNeededToFadeOut(u32(xmlReader->getAttributeValueAsInt("FadeOutAffectorTimeNeededToFadeOut")));
					model.addAffectorType(ParticleModel::AffectorTypes::FADE_OUT);
				}
				else if (!strcmp("AttractionAffectorPoint", xmlReader->getNodeName()))
				{
					model.setAttractionAffectorPoint(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));
				}
				else if (!strcmp("ATTRACT_Rest", xmlReader->getNodeName()))
				{
					model.setAttractionAffectorAttract(s32(xmlReader->getAttributeValueAsInt("AttractionAffectorAttract")));
					model.setAttractionAffectorSpeed(f32(xmlReader->getAttributeValueAsFloat("AttractionAffectorSpeed")));
					model.setAttractionAffectorAffectX(s32(xmlReader->getAttributeValueAsInt("AttractionAffectorAffectX")));
					model.setAttractionAffectorAffectY(s32(xmlReader->getAttributeValueAsInt("AttractionAffectorAffectY")));
					model.setAttractionAffectorAffectZ(s32(xmlReader->getAttributeValueAsInt("AttractionAffectorAffectZ")));
					model.addAffectorType(ParticleModel::AffectorTypes::ATTRACT);
				}
				else if (!strcmp("GravityAffectorGravity", xmlReader->getNodeName()))
				{
					model.setGravityAffectorGravity(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));
				}
				else if (!strcmp("GRAVITY_Rest", xmlReader->getNodeName()))
				{
					model.setGravityAffectorTimeForceLost(u32(xmlReader->getAttributeValueAsInt("GravityAffectorTimeForceLost")));
					model.addAffectorType(ParticleModel::AffectorTypes::GRAVITY);
				}
				else if (!strcmp("RotationAffectorSpeed", xmlReader->getNodeName()))
				{
					model.setRotationAffectorSpeed(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));
				}
				else if (!strcmp("RotationAffectorPivotPoint", xmlReader->getNodeName()))
				{
					model.setRotationAffectorPivotPoint(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));
					model.addAffectorType(ParticleModel::AffectorTypes::ROTATE);
				}
				else if (!strcmp("ScaleAffectorScaleTo", xmlReader->getNodeName()))
				{
					model.setScaleAffectorScaleTo(core::dimension2df(xmlReader->getAttributeValueAsFloat("Width"), xmlReader->getAttributeValueAsFloat("Height")));
					model.addAffectorType(ParticleModel::AffectorTypes::SCALE);
				}
			}
			break;
		}
	}
	
	// Delete the xml parser after usage
	delete xmlReader;

	return model;
}

// Deconstructor
ParticleParser::~ParticleParser()
{
}
