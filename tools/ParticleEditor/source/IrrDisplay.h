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
	void setupIrrlicht( IrrlichtDevice* device );
	void displayParticle (ParticleModel* model);
	~IrrDisplay(void);
private:
	IrrlichtDevice* device;
	scene::ISceneManager* manager;
	video::IVideoDriver* driver;
	ParticleManager* pManager;
};

#endif