#include "IrrDisplay.h"
#include "ParticleModel.h"
#include "ParticleManager.h"
#include "InputReceiver.h"

IrrDisplay::IrrDisplay(InputReceiver* inputReceiver)
{
	activeParticle = nullptr;
	this->inputReceiver = inputReceiver;
}

void IrrDisplay::setupIrrlicht( IrrlichtDevice* device )
{
	// Check if the IrrlichtWidget successfully created an Irrlicht device
    if (!device) {
        std::cout << "No device!" << std::endl;
        return;
    }
	this->device = device;

	// Get the irrlicht scene manager
    manager = device->getSceneManager();
    if (!manager) {
        std::cout << "No manager!" << std::endl;
        return;
    }

	// Get the irrlicht video driver
    driver = device->getVideoDriver();
    if (!driver) {
        std::cout << "No driver!" << std::endl;
        return;
    }

	// Get the particle manager
	pManager = new ParticleManager(driver, device, manager);

    // Create a camera to view the box
    cam = manager->addCameraSceneNode(0, core::vector3df(0,10,-20), core::vector3df(0,10,0));
}

void IrrDisplay::update()
{
	core::vector3df pos = cam->getPosition();

	// Zoom with the scroll wheel
	pos.Z = -20 + inputReceiver->mouseWheel;

	// Move with the mouse, when zoomed out move faster
	pos.X += ((float) inputReceiver->deltaMouse.X / 30) * (-pos.Z / 10);
	pos.Y -= ((float) inputReceiver->deltaMouse.Y / 30) * (-pos.Z / 10);

	cam->setPosition(pos);

	// Target is a bit behind the particle
	pos.Z += 10;
	cam->setTarget(pos);
}

void IrrDisplay::displayParticle (ParticleModel* model)
{
	if (activeParticle != nullptr) {
		activeParticle->remove();
	}
	
	// Spawn a particle based on a particle model
	activeParticle = pManager->spawnDataModelParticle(model, core::vector3df(0,0,0), model->getPathNameTexture());
}

IrrDisplay::~IrrDisplay(void)
{
}
