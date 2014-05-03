#ifndef PARTICLEPARSER_H_
#define PARTICLEPARSER_H_

#include "irrlicht.h"
#include "ParticleModel.h"

using namespace irr;

/*
 This class is used for reading values from a XML file
 and store these values in a model which got the attributes
 of the ParticleModel class. In the ParticleManager::spawnXMLParticle function the model will be
 parsed to the particle model. An example of how you call a particle
 in your gamecode looks like this:

 pManager->spawnXMLParticle("../../Media/levelParticles.xml", core::vector3df(4,2,2));

 For each particle there can be a attribute pathNameTexture.
 This pathNameTexture should be located in the same folder as
 the XML file which this class is reading.
*/

class IRRLICHT_API ParticleParser
{
public:
	// The default constructor
	ParticleParser();

	/* This function loops through the XML file to read all the values
	which are stored in the XML file. The values are stored to a model
	by using setters which are defined in the ParticleModel class.
	*/
	ParticleModel parse(const char* filename);


	// Deconstructor
	~ParticleParser(void);
private:

};

#endif