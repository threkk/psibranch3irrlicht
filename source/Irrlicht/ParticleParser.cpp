#include "ParticleParser.h"
#include "string"

using namespace irr;


ParticleParser::ParticleParser()
{
	// Creates a XML reader and set path to load the XML file from
	io::IrrXMLReader* xmlReader = io::createIrrXMLReader("../../Media/test.xml");

	ParticleModel model;

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

					std::cout << "Direction: " << model.getDirection().X << std::endl;
					std::cout << "Direction: " << model.getDirection().Y << std::endl;
					std::cout << "Direction: " << model.getDirection().Z << std::endl;
					
				}
				else if (!strcmp("Emitter", xmlReader->getNodeName()))
				{
					model.setEmitterType(ParticleModel::EmitterTypes(xmlReader->getAttributeValueAsInt("Type")));

					std::cout << "Emitter type: " << model.getEmitterType() << std::endl;
					
				}
				else if (!strcmp("Aabbox", xmlReader->getNodeName()))
				{
					model.setAabbox(core::aabbox3df(xmlReader->getAttributeValueAsFloat("MinX"), xmlReader->getAttributeValueAsFloat("MinY"),
					xmlReader->getAttributeValueAsFloat("MinZ"), xmlReader->getAttributeValueAsFloat("MaxX"),
					xmlReader->getAttributeValueAsFloat("MaxY"), xmlReader->getAttributeValueAsFloat("MaxZ")));

					std::cout << "Aabbox: minX" << model.getAabbox().MinEdge.X << " minY : " << model.getAabbox().MinEdge.Y << " minZ : " << model.getAabbox().MinEdge.Z << std::endl;
					std::cout << "Aabbox: maxX" << model.getAabbox().MaxEdge.X << " maxY : " << model.getAabbox().MaxEdge.Y << " maxZ : " << model.getAabbox().MaxEdge.Z << std::endl;

				}
				else if (!strcmp("Position", xmlReader->getNodeName()))
				{
					model.setPosition(core::vector3df(xmlReader->getAttributeValueAsFloat("X"),
					xmlReader->getAttributeValueAsFloat("Y"), posZ = xmlReader->getAttributeValueAsFloat("Z")));

					std::cout << "Position: X: " << model.getPosition().X << " Position Y: " << model.getPosition().Y << " Position Z: " << model.getPosition().Z << std::endl;
				}
				else if (!strcmp("Center", xmlReader->getNodeName()))
				{
					model.setCenter(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));

					std::cout << "Center X: " << model.getCenter().X << " Center Y: " <<  model.getCenter().Y << " Center Z: " << model.getCenter().Z << std::endl;
				}
				else if (!strcmp("Normal", xmlReader->getNodeName()))
				{
					model.setNormal(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));

					std::cout << "Normal X: " << model.getNormal().X << " Normal Y: " << model.getNormal().Y << " Normal Z: " << model.getNormal().Z << std::endl;
				}
				else if (!strcmp("AngleDegrees", xmlReader->getNodeName()))
				{
					model.setMaxAngleDegrees(s32(xmlReader->getAttributeValueAsInt("Max")));

					std::cout << "Angle: " << model.getMaxAngleDegrees() << std::endl;
				}
				else if (!strcmp("LifeTime", xmlReader->getNodeName()))
				{
					model.setLifeTimeMax(u32(xmlReader->getAttributeValueAsInt("Max")));
					model.setLifeTimeMin(u32(xmlReader->getAttributeValueAsInt("Min")));

					std::cout << "Lifetime Min: " << model.getLifeTimeMin() << " Max: " << model.getLifeTimeMax() << std::endl;
				}
				else if (!strcmp("PPS", xmlReader->getNodeName()))
				{
					model.setMaxPPS(u32(xmlReader->getAttributeValueAsInt("Max")));
					model.setMinPPS(u32(xmlReader->getAttributeValueAsInt("Min")));

					std::cout << "PPS Min: " << model.getMinPPS() << " Max: " << model.getMaxPPS() << std::endl;
				}
				else if (!strcmp("MaxStartColor", xmlReader->getNodeName()))
				{
					model.setMaxColor(video::SColor(xmlReader->getAttributeValueAsInt("Alpha"), xmlReader->getAttributeValueAsInt("Red"),
						xmlReader->getAttributeValueAsInt("Blue"), xmlReader->getAttributeValueAsInt("Green")));

					
				}
				else if (!strcmp("MinStartColor", xmlReader->getNodeName()))
				{
					model.setMinColor(video::SColor(xmlReader->getAttributeValueAsInt("Alpha"), xmlReader->getAttributeValueAsInt("Red"),
						xmlReader->getAttributeValueAsInt("Blue"), xmlReader->getAttributeValueAsInt("Green")));
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
					model.setPathNameTexture(core::stringc(xmlReader->getAttributeValue("PathName")));
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
