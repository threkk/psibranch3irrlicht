#ifndef PARTICLEPARSER_H_
#define PARTICLEPARSER_H_

#include "irrlicht.h"
#include "ParticleModel.h"

using namespace irr;

/*
 This class is used for reading values from a XML file
 and store these values in a model which got the attributes
 of the ParticleModel class. This model can be used to create
 particles. For each particle there can be a attribute pathNameTexture.
 This pathNameTexture should be located in the same folder as
 the XML file which this class is reading.
 
*/

class IRRLICHT_API ParticleParser
{
public:
	// The default constructor
	ParticleParser();

	// XML file reader
	ParticleModel parse(const char* filename);


	// Deconstructor
	~ParticleParser(void);
private:

};

#endif