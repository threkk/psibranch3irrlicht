#include <qstring.h>
#include <QApplication>
#include <qpushbutton.h>
#include <QVBoxLayout>
#include "QIrrlichtWidget.h"
#include <irrlicht.h>
#include <iostream>
#include "mainwindow.h"
#include "ParticleModel.h"
#include "ParticleManager.h"
#include "IrrDisplay.h"

using namespace irr;

int main(int argc, char **argv)
{
    std::cout << "Start main" << std::endl;

    QApplication a(argc, argv);

    // Create the particle model which keeps the values in memory
    ParticleModel* m = new ParticleModel();
	m->setPathNameTexture("../../../../Media/smoke.png");
	m->setDirection(core::vector3df(0, 0.01, 0));
	m->setLifeTimeMin(1300);
	m->setLifeTimeMax(1500);
	m->setMaxStartSize(core::dimension2df(1.5,1.5));
	m->setMinStartSize(core::dimension2df(1,1));

    // Create the window
    MainWindow w;

    // Show the window
    w.show();

    // Add the particle model to the window
    w.setParticleModel (m);

	w.resize(800, 600);

    QLayout* layout = w.layout();

    QIrrlichtWidget irrWidget;
    
    irrWidget.init();

	IrrDisplay irrDisplay = IrrDisplay();
	irrDisplay.setupIrrlicht( irrWidget.getIrrlichtDevice() );
	irrDisplay.displayParticle(m);

	layout->addWidget(&irrWidget);
	irrWidget.setParent(w.findChild<QWidget*>("centralWidget"));
	irrWidget.move(10, 10);
	irrWidget.resize(540, 480);

	/*QWidget* from = w.findChild<QWidget*>("irr_widget");
	if (from != nullptr) {
		layout->replaceWidget(from, &irrWidget);
	} else {
		std::cout << "Cant replace" << std::endl;
	}*/

    return a.exec();
}
