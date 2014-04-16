#include "mainwindow.h"
#include <ParticleModel.h>
#include "ui_mainwindow.h"
#include "XML.h"
#include <iostream>
#include <QColorDialog>

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
    xml.SaveXML(model);
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

void MainWindow::on_pushButton_Color_Min_clicked()
{
    QColor color = QColorDialog::getColor(Qt::green);

    QPushButton* button = this->findChild<QPushButton*>("pushButton_Color_Min");
    QString style = "background-color: rgb(%1, %2, %3);border: 0;text-align:left;padding-left:5px;";
    button->setStyleSheet(style.arg(color.red()).arg(color.green()).arg(color.blue()));

    model->setMinColor(video::SColor(color.alpha(), color.red(), color.green(), color.blue()));

    std::cout << "Change of min color: " << model->getMinStartColor().getAlpha() << ", " << model->getMinStartColor().getRed() << ", " << model->getMinStartColor().getBlue() << ", " << model->getMinStartColor().getGreen() << std::endl;
}

void MainWindow::on_pushButton_Color_Max_clicked()
{
    QColor color = QColorDialog::getColor(Qt::green);

    QPushButton* button = this->findChild<QPushButton*>("pushButton_Color_Max");
    QString style = "background-color: rgb(%1, %2, %3);border: 0;text-align:left;padding-left:5px;";
    button->setStyleSheet(style.arg(color.red()).arg(color.green()).arg(color.blue()));

    model->setMaxColor(video::SColor(color.alpha(), color.red(), color.green(), color.blue()));

    std::cout << "Change of max color: " << model->getMaxStartColor().getAlpha() << ", " << model->getMaxStartColor().getRed() << ", " << model->getMaxStartColor().getBlue() << ", " << model->getMaxStartColor().getGreen() << std::endl;
}

void MainWindow::on_lineEdit_Angle_textChanged(const QString &arg1)
{
    model->setMaxAngleDegrees(arg1.toFloat());
    std::cout << "Change of angle: " << model->getMaxAngleDegrees() << std::endl;
}

void MainWindow::on_lineEdit_Lifetime_Min_textChanged(const QString &arg1)
{
    model->setLifeTimeMin(arg1.toFloat());
    std::cout << "Change of min life time: " << model->getLifeTimeMin() << std::endl;
}

void MainWindow::on_lineEdit_Lifetime_Max_textChanged(const QString &arg1)
{
    model->setLifeTimeMax(arg1.toFloat());
    std::cout << "Change of max life time: " << model->getLifeTimeMax() << std::endl;
}

void MainWindow::on_lineEdit_PPS_Min_textChanged(const QString &arg1)
{
    model->setMinPPS(arg1.toFloat());
    std::cout << "Change of min pps: " << model->getMinPPS() << std::endl;
}

void MainWindow::on_lineEdit_PPS_Max_textChanged(const QString &arg1)
{
    model->setMaxPPS(arg1.toFloat());
    std::cout << "Change of max pps: " << model->getMaxPPS() << std::endl;
}

void MainWindow::on_lineEdit_MinStartSize_X_textChanged(const QString &arg1)
{
    model->setMinStartSize(core::dimension2df(arg1.toFloat(), model->getMinStartSize().Height));
    std::cout << "Change of min start size: " << model->getMinStartSize().Width << ", " << model->getMinStartSize().Height << std::endl;
}

void MainWindow::on_lineEdit_MinStartSize_Y_textChanged(const QString &arg1)
{
    model->setMinStartSize(core::dimension2df(model->getMinStartSize().Width, arg1.toFloat()));
    std::cout << "Change of min start size: " << model->getMinStartSize().Width << ", " << model->getMinStartSize().Height << std::endl;
}

void MainWindow::on_lineEdit_MaxStartSize_X_textChanged(const QString &arg1)
{
    model->setMaxStartSize(core::dimension2df(arg1.toFloat(), model->getMaxStartSize().Height));
    std::cout << "Change of max start size: " << model->getMaxStartSize().Width << ", " << model->getMaxStartSize().Height << std::endl;
}

void MainWindow::on_lineEdit_MaxStartSize_Y_textChanged(const QString &arg1)
{
    model->setMaxStartSize(core::dimension2df(model->getMaxStartSize().Width, arg1.toFloat()));
    std::cout << "Change of max start size: " << model->getMaxStartSize().Width << ", " << model->getMaxStartSize().Height << std::endl;
}

void MainWindow::on_comboBox_EmitterType_currentIndexChanged(int index)
{
    model->setEmitterType(static_cast<ParticleModel::EmitterTypes>(index));
    std::cout << "Change of emitter type: " << model->getEmitterType() << std::endl;
}
