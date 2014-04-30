#ifndef PARTICLEPARSER_H_
#define PARTICLEPARSER_H_

#include "irrlicht.h"
#include "ParticleModel.h"

using namespace irr;

class IRRLICHT_API ParticleParser
{
public:
	ParticleParser();
	ParticleModel parse(const char* filename);
	~ParticleParser(void);
private:

};

#endif