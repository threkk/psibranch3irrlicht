#include <qstring.h>
#include <QApplication>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include "QIrrlichtWidget.h"
#include <irrlicht.h>
#include "mainwindow.h"
#include "ParticleModel.h"

using namespace irr;

void setupIrrlicht( IrrlichtDevice* device )
{
    // Get the scene manager
    scene::ISceneManager* manager = device->getSceneManager();
    video::IVideoDriver* driver = device->getVideoDriver();

    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
            core::rect<s32>(10,10,260,22), true);

    IAnimatedMesh* mesh = manager->getMesh("../../../media/sydney.md2");
    if (!mesh)
    {
        device->drop();
        return;
    }
    IAnimatedMeshSceneNode* node = manager->addAnimatedMeshSceneNode( mesh );
    if (node)
    {
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
    }

    // Create a small box
    // scene::ISceneNode* node = manager->addSphereSceneNode();
    // node->setMaterialFlag( video::EMF_LIGHTING, false );

    // Create a camera to view the box
    scene::ICameraSceneNode* cam = manager->addCameraSceneNode(0, core::vector3df(0,30,-40), core::vector3df(0,5,0));

    //manager->addCameraSceneNode();

    //cam->setPosition( core::vector3df(100,100,0) );
    //cam->setTarget( core::vector3df(0,0,0) );

    // scene::ISceneNodeAnimator* anim = manager->createFlyCircleAnimator( core::vector3df(0,0,0), 20 );
    // node->addAnimator(anim);
    // anim->drop();
}

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    // Create the particle model which keeps the values in memory
    ParticleModel* m = new ParticleModel();

    // Create the window
    MainWindow w;

    // Show the window
    w.show();

    // Add the particle model to the window
    w.setParticleModel (m);

    QLayout* layout = w.layout();

    QIrrlichtWidget irrWidget;
    layout->addWidget(&irrWidget);

    irrWidget.init();

    setupIrrlicht( irrWidget.getIrrlichtDevice() );

    return a.exec();
}
