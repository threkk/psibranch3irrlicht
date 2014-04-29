#include "IrrDisplay.h"
#include "ParticleModel.h"
#include "ParticleManager.h"

IrrDisplay::IrrDisplay(void)
{
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
    scene::ICameraSceneNode* cam = manager->addCameraSceneNode(0, core::vector3df(0,10,-20), core::vector3df(0,10,0));
}

void IrrDisplay::displayParticle (ParticleModel* model)
{
	pManager->spawnDataModelParticle(model, core::vector3df(0,0,0), model->getPathNameTexture());
}

IrrDisplay::~IrrDisplay(void)
{
}
