#include "mainwindow.h"
#include <ParticleModel.h>
#include "ui_mainwindow.h"
#include "XML.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setParticleModel(ParticleModel* model)
{
    this->model = model;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_name_textChanged(const QString &arg1)
{
    // TODO
}


void MainWindow::on_actionSave_XML_triggered()
{
    std::cout << "Save to xml: " << std::endl;
    std::cout << " " << model->toString() << " " << std::endl;
    XML xml;
    xml.SaveXML();
}

void MainWindow::on_lineEdit_Direction_X_textChanged(const QString &arg1)
{
    model->setDirection(core::vector3df (arg1.toFloat(), model->getDirection().Y, model->getDirection().Z));
    std::cout << "Change of direction: " << model->getDirection().X << ", " << model->getDirection().Y << ", " << model->getDirection().Z << std::endl;
}

void MainWindow::on_lineEdit_Direction_Y_textChanged(const QString &arg1)
{
    model->setDirection(core::vector3df (model->getDirection().X, arg1.toFloat(), model->getDirection().Z));
    std::cout << "Change of direction: " << model->getDirection().X << ", " << model->getDirection().Y << ", " << model->getDirection().Z << std::endl;
}

void MainWindow::on_lineEdit_Direction_Z_textChanged(const QString &arg1)
{
    model->setDirection(core::vector3df (model->getDirection().X, model->getDirection().Y, arg1.toFloat()));
    std::cout << "Change of direction: " << model->getDirection().X << ", " << model->getDirection().Y << ", " << model->getDirection().Z << std::endl;
}
