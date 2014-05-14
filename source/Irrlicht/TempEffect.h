#ifndef TEMPEFFECT_H_
#define TEMPEFFECT_H_

#include "irrlicht.h"
using namespace irr;

class IRRLICHT_API TempEffect
{
public:
	// The default constructor
	TempEffect();

	// Function which checks if the particle effect is expired
	bool isOver(int currentTime);

	// The deconstructor
	~TempEffect(void);

private:

	IParticleSystemSceneNode* node;
	int startTime;

};

#endif