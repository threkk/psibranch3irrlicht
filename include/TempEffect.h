#ifndef TEMPEFFECT_H_
#define TEMPEFFECT_H_

#include "irrlicht.h"

using namespace irr;

class IRRLICHT_API TempEffect
{
public:
	// The default constructor
	TempEffect(scene::IParticleSystemSceneNode* particleNode, u32 startTime, u32 stopEmitting, u32 removeParticleAfter);

	// Function which checks if the particle effect should stop emitting
	bool isOver(u32 currentTime);

	// The deconstructor
	~TempEffect(void);

	IParticleSystemSceneNode* node;

private:
	/* Variables for tracking the startTime of the particle
	   and after x seconds he should stop emit the particle
	   and/or remove the particle. */
	int startTime;
	u32 stopEmitting, removeParticleAfter;

};

#endif