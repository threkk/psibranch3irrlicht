#include <qstring.h>
#include <QApplication>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include "QIrrlichtWidget.h"
#include <irrlicht.h>
#include <iostream>
#include "mainwindow.h"
#include "ParticleModel.h"

using namespace irr;

void setupIrrlicht( IrrlichtDevice* device )
{
    if (!device) {
        std::cout << "No device!" << std::endl;
        return;
    }

    // Get the scene manager
    scene::ISceneManager* manager = device->getSceneManager();
    if (!manager) {
        std::cout << "No manager!" << std::endl;
        return;
    }

    video::IVideoDriver* driver = device->getVideoDriver();
    if (!driver) {
        std::cout << "No driver!" << std::endl;
        return;
    }

    std::cout << "Device, manager and driver created" << std::endl;

    //gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    //guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", core::rect<s32>(10,10,10,22), true);

    std::cout << "1" << std::endl;
    scene::IAnimatedMesh* mesh;
    std::cout << "2" << std::endl;
    mesh = manager->getMesh("../../media/sydney.md2");
    std::cout << "3" << std::endl;
    if (mesh)
    {
        scene::IAnimatedMeshSceneNode* node = manager->addAnimatedMeshSceneNode( mesh );
        if (node)
        {
            node->setMaterialFlag(video::EMF_LIGHTING, false);
            node->setMD2Animation(scene::EMAT_STAND);
            node->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
			std::cout << "Mesh node created at " << node->getPosition().X << "," << node->getPosition().Y << "," << node->getPosition().Z << std::endl;
        }
        else
        {
            std::cout << "No node!" << std::endl;
        }
    }
    else
    {
        std::cout << "No mesh!" << std::endl;
    }


    // Create a small box
    // scene::ISceneNode* node = manager->addSphereSceneNode();
    // node->setMaterialFlag( video::EMF_LIGHTING, false );

    // Create a camera to view the box
    scene::ICameraSceneNode* cam = manager->addCameraSceneNode(0, core::vector3df(0,10,-10), core::vector3df(0,0,0));

    //manager->addCameraSceneNode();

    //cam->setPosition( core::vector3df(100,100,0) );
    //cam->setTarget( core::vector3df(0,0,0) );

    // scene::ISceneNodeAnimator* anim = manager->createFlyCircleAnimator( core::vector3df(0,0,0), 20 );
    // node->addAnimator(anim);
    // anim->drop();
}

int main(int argc, char **argv)
{
    std::cout << "Start main" << std::endl;

    QApplication a(argc, argv);

    // Create the particle model which keeps the values in memory
    ParticleModel* m = new ParticleModel();

    // Create the window
    MainWindow w;

    // Show the window
    w.show();

    // Add the particle model to the window
    w.setParticleModel (m);

	w.resize(800,600);

    QLayout* layout = w.layout();

    QIrrlichtWidget irrWidget;
    
    irrWidget.init();

    std::cout << "Setup Irrlicht" << std::endl;

    setupIrrlicht( irrWidget.getIrrlichtDevice() );
	layout->addWidget(&irrWidget);
	//QWidget* q = layout->findChild<QWidget*>("graphicsView");
	//layout->replaceWidget(q, &irrWidget);

    return a.exec();
}
