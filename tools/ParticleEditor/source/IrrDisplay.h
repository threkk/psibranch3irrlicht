#ifndef IRRDISPLAY_H_
#define IRRDISPLAY_H_

#include <irrlicht.h>

class ParticleModel;
class ParticleManager;
class InputReceiver;

using namespace irr;

class IrrDisplay
{
public:
	IrrDisplay(InputReceiver* inputReceiver);

	/**
	 * Set up a new irrlicht instantiation based on a given device
	 */
	void setupIrrlicht( IrrlichtDevice* device );

	/**
	 * Show a particle based on a given particle model
	 */
	void displayParticle (ParticleModel* model);

	void update(void);

	~IrrDisplay(void);

private:

	// The default irrlicht values
	IrrlichtDevice* device;
	scene::ISceneManager* manager;
	video::IVideoDriver* driver;

	// Particle manager, takes care of spawning particles
	ParticleManager* pManager;

	scene::IParticleSystemSceneNode* activeParticle;

	// Handles the input in the irrlicht view
	InputReceiver* inputReceiver;

	// The camera which points at the effect
	scene::ICameraSceneNode* cam;
};

#endif