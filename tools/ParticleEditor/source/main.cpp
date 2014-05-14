#include <iostream>

#include <QString.h>
#include <QApplication>
#include <QPushButton.h>
#include <QVBoxLayout>

#include <irrlicht.h>
#include "ParticleManager.h"
#include "ParticleModel.h"

#include "mainwindow.h"
#include "QIrrlichtWidget.h"
#include "IrrDisplay.h"
#include "InputReceiver.h"

using namespace irr;

int main(int argc, char **argv)
{
	// Start the Qt application
    QApplication a(argc, argv);

    // Create the particle model which keeps the values in memory
    ParticleModel m = ParticleModel();

	// Change some default values so that we have a nice demo (can be removed in the future)
	m.setPathNameTexture("../../../../Media/smoke.png");
	m.setDirection(core::vector3df(0, 0.01, 0));
	m.setLifeTimeMin(1300);
	m.setLifeTimeMax(1500);
	m.setMaxStartSize(core::dimension2df(1.5,1.5));
	m.setMinStartSize(core::dimension2df(1,1));

    // Create and show the window
    MainWindow w;
    w.show();

	// For now we work a 900x675 editor
	w.resize(1100, 675);

	// Get the layout from the ui
    QLayout* layout = w.layout();

	// Create the irrlicht widget
    QIrrlichtWidget irrWidget;
	InputReceiver* inputReceiver = new InputReceiver;
	IrrDisplay irrDisplay = IrrDisplay(inputReceiver);
    irrWidget.init(inputReceiver, &irrDisplay);

	// Initialize our display class and make it build up an irrlicht instaniation
	irrDisplay.setupIrrlicht( irrWidget.getIrrlichtDevice() );
	irrDisplay.displayParticle(&m);

	// Add the irrlicht widget to the layout after irrlicht is linked to it
	layout->addWidget(&irrWidget);
	irrWidget.setParent(w.findChild<QWidget*>("centralWidget"));
	irrWidget.move(10, 10);
	irrWidget.resize(540, 480);

    // Add the particle model to the window
    w.setIrrDisplay (&irrDisplay);
    w.setParticleModel (m);

    return a.exec();
}
