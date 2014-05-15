#ifndef TEMPEFFECT_H_
#define TEMPEFFECT_H_

#include "irrlicht.h"

using namespace irr;

class IRRLICHT_API TempEffect
{
public:
	// The default constructor
	TempEffect(scene::IParticleSystemSceneNode* particleNode, u32 startTime, u32 StopEmitting, u32 RemoveParticleAfter);

	// Function which checks if the particle effect is expired
	bool isOver(u32 currentTime);

	// The deconstructor
	~TempEffect(void);

private:

	IParticleSystemSceneNode* node;
	int startTime;

};

#endif