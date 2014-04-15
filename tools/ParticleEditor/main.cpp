#include "mainwindow.h"
#include <irrlicht.h>
#include <ParticleModel.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    irr::core::vector3df test;
    ParticleModel m;

    MainWindow w;
    w.show();
   // w.setParticleModel (m);

    return a.exec();
}
