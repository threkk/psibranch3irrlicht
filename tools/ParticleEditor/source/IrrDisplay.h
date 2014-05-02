#ifndef IRRDISPLAY_H_
#define IRRDISPLAY_H_

#include <irrlicht.h>

class ParticleModel;
class ParticleManager;

using namespace irr;

class IrrDisplay
{
public:
	IrrDisplay(void);

	/**
	 * Set up a new irrlicht instantiation based on a given device
	 */
	void setupIrrlicht( IrrlichtDevice* device );

	/**
	 * Show a particle based on a given particle model
	 */
	void displayParticle (ParticleModel* model);

	~IrrDisplay(void);

private:

	// The default irrlicht values
	IrrlichtDevice* device;
	scene::ISceneManager* manager;
	video::IVideoDriver* driver;

	// Particle manager, takes care of spawning particles
	ParticleManager* pManager;

	scene::IParticleSystemSceneNode* activeParticle;
};

#endif