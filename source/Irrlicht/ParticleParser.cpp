#include "ParticleParser.h"
#include "string"

using namespace irr;


ParticleParser::ParticleParser()
{
	// Creates a XML reader and set path to load the XML file from
	io::IrrXMLReader* xmlReader = io::createIrrXMLReader("../../Media/test.xml");

	ParticleModel modelXML;

	while (xmlReader && xmlReader->read())
	{
		switch (xmlReader->getNodeType())
		{
			// Search for elements in the XML file and store them in the model
		case io::EXN_ELEMENT:
			{
				if (!strcmp("Direction", xmlReader->getNodeName()))
				{
					modelXML.setDirection(core::vector3df(xmlReader->getAttributeValueAsFloat("X"),
						xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));

					std::cout << "Direction: " << modelXML.getDirection().X << std::endl;
					std::cout << "Direction: " << modelXML.getDirection().Y << std::endl;
					std::cout << "Direction: " << modelXML.getDirection().Z << std::endl;
					
				}
				else if (!strcmp("Emitter", xmlReader->getNodeName()))
				{
					modelXML.setEmitterType(ParticleModel::EmitterTypes(xmlReader->getAttributeValueAsInt("Type")));

					std::cout << "Emitter type: " << modelXML.getEmitterType() << std::endl;
					
				}
				else if (!strcmp("Aabbox", xmlReader->getNodeName()))
				{
					modelXML.setAabbox(core::aabbox3df(xmlReader->getAttributeValueAsFloat("MinX"), xmlReader->getAttributeValueAsFloat("MinY"),
					xmlReader->getAttributeValueAsFloat("MinZ"), xmlReader->getAttributeValueAsFloat("MaxX"),
					xmlReader->getAttributeValueAsFloat("MaxY"), xmlReader->getAttributeValueAsFloat("MaxZ")));

					std::cout << "Aabbox: minX : " << modelXML.getAabbox().MinEdge.X << " minY : " << modelXML.getAabbox().MinEdge.Y << " minZ : " << modelXML.getAabbox().MinEdge.Z << std::endl;
					std::cout << "Aabbox: maxX : " << modelXML.getAabbox().MaxEdge.X << " maxY : " << modelXML.getAabbox().MaxEdge.Y << " maxZ : " << modelXML.getAabbox().MaxEdge.Z << std::endl;

				}
				else if (!strcmp("Position", xmlReader->getNodeName()))
				{
					modelXML.setPosition(core::vector3df(xmlReader->getAttributeValueAsFloat("X"),
					xmlReader->getAttributeValueAsFloat("Y"), xmlReader->getAttributeValueAsFloat("Z")));

					std::cout << "Position: X: " << modelXML.getPosition().X << " Position Y: " << modelXML.getPosition().Y << " Position Z: " << modelXML.getPosition().Z << std::endl;
				}
				else if (!strcmp("Center", xmlReader->getNodeName()))
				{
					modelXML.setCenter(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));

					std::cout << "Center X: " << modelXML.getCenter().X << " Center Y: " <<  modelXML.getCenter().Y << " Center Z: " << modelXML.getCenter().Z << std::endl;
				}
				else if (!strcmp("Normal", xmlReader->getNodeName()))
				{
					modelXML.setNormal(core::vector3df(xmlReader->getAttributeValueAsFloat("X"), xmlReader->getAttributeValueAsFloat("Y"),
						xmlReader->getAttributeValueAsFloat("Z")));

					std::cout << "Normal X: " << modelXML.getNormal().X << " Normal Y: " << modelXML.getNormal().Y << " Normal Z: " << modelXML.getNormal().Z << std::endl;
				}
				else if (!strcmp("AngleDegrees", xmlReader->getNodeName()))
				{
					modelXML.setMaxAngleDegrees(s32(xmlReader->getAttributeValueAsInt("Max")));

					std::cout << "Angle: " << modelXML.getMaxAngleDegrees() << std::endl;
				}
				else if (!strcmp("LifeTime", xmlReader->getNodeName()))
				{
					modelXML.setLifeTimeMax(u32(xmlReader->getAttributeValueAsInt("Max")));
					modelXML.setLifeTimeMin(u32(xmlReader->getAttributeValueAsInt("Min")));

					std::cout << "Lifetime Min: " << modelXML.getLifeTimeMin() << " Max: " << modelXML.getLifeTimeMax() << std::endl;
				}
				else if (!strcmp("PPS", xmlReader->getNodeName()))
				{
					modelXML.setMaxPPS(u32(xmlReader->getAttributeValueAsInt("Max")));
					modelXML.setMinPPS(u32(xmlReader->getAttributeValueAsInt("Min")));

					std::cout << "PPS Min: " << modelXML.getMinPPS() << " Max: " << modelXML.getMaxPPS() << std::endl;
				}
				else if (!strcmp("MaxStartColor", xmlReader->getNodeName()))
				{
					modelXML.setMaxColor(video::SColor(xmlReader->getAttributeValueAsInt("Alpha"), xmlReader->getAttributeValueAsInt("Red"),
						xmlReader->getAttributeValueAsInt("Blue"), xmlReader->getAttributeValueAsInt("Green")));

					
				}
				else if (!strcmp("MinStartColor", xmlReader->getNodeName()))
				{
					modelXML.setMinColor(video::SColor(xmlReader->getAttributeValueAsInt("Alpha"), xmlReader->getAttributeValueAsInt("Red"),
						xmlReader->getAttributeValueAsInt("Blue"), xmlReader->getAttributeValueAsInt("Green")));
				}
				else if (!strcmp("MaxStartSize", xmlReader->getNodeName()))
				{
					modelXML.setMaxStartSize(core::dimension2df(xmlReader->getAttributeValueAsFloat("Width"), xmlReader->getAttributeValueAsFloat("Height")));
				}
				else if (!strcmp("MinStartSize", xmlReader->getNodeName()))
				{
					modelXML.setMinStartSize(core::dimension2df(xmlReader->getAttributeValueAsFloat("Width"), xmlReader->getAttributeValueAsFloat("Height")));
				}
				else if (!strcmp("Texture", xmlReader->getNodeName()))
				{
					modelXML.setPathNameTexture(core::stringc(xmlReader->getAttributeValue("PathName")));
				}
				else if (!strcmp("Rest", xmlReader->getNodeName()))
				{
					modelXML.setOutLineOnly(s32(xmlReader->getAttributeValueAsInt("OutLineOnly")));
					modelXML.setEveryMeshVertex(s32(xmlReader->getAttributeValueAsInt("EveryMeshVertex")));
					modelXML.setUseNormalDirection(s32(xmlReader->getAttributeValueAsInt("UseNormalDirection")));
					modelXML.setRingThickness(f32(xmlReader->getAttributeValueAsFloat("RingThickness")));
					modelXML.setLengthCylinder(f32(xmlReader->getAttributeValueAsFloat("LengthCylinder")));
					modelXML.setRadius(f32(xmlReader->getAttributeValueAsFloat("Radius")));
					modelXML.setNormalDirectionModifier(f32(xmlReader->getAttributeValueAsFloat("NormalDirectionModifier")));
					modelXML.setMbNumber(s32(xmlReader->getAttributeValueAsInt("MbNumber")));
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
