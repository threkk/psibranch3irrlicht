#include "mainwindow.h"
#include <irrlicht.h>
#include "ParticleModel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ParticleModel* m = new ParticleModel();


    MainWindow w;
    w.show();
    w.setParticleModel (m);

    return a.exec();
}
