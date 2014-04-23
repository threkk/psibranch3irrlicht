#include "mainwindow.h"
#include <irrlicht.h>
#include "ParticleModel.h"
#include <QApplication>

int main(int argc, char *argv[])
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

    return a.exec();
}
