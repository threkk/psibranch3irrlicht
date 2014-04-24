#include "ParticleParser.h"
#include "string"

using namespace irr;


ParticleParser::ParticleParser()
{
	// Creates a XML reader and set path to load the XML file from
	io::IrrXMLReader* xmlReader = io::createIrrXMLReader("../../Media/test.xml");

	ParticleModel model;

	float x, y, z; // floats for the direction of the particle
	int type; // emitter type

	while (xmlReader && xmlReader->read())
	{
		switch (xmlReader->getNodeType())
		{
			// Search for elements in the XML file and store them in the model
		case io::EXN_ELEMENT:
			{
				if (!strcmp("Direction", xmlReader->getNodeName()))
				{
					model.setDirection(core::vector3df(xmlReader->getAttributeValueAsFloat("X"),
						xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));
				}
				else if (!strcmp("Emitter", xmlReader->getNodeName()))
				{
					//model.setEmitterType(xmlReader->getAttributeValueAsInt("type")));
					
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
					xmlReader->getAttributeValueAsFloat("Y"), posZ = xmlReader->getAttributeValueAsFloat("Z")));
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
			}
			break;
		}
	}
	
	// Delete the xml parser after usage
	delete xmlReader;

}

// Deconstructor
ParticleParser::~ParticleParser()
{
}
