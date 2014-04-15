#include "mainwindow.h"
#include "ParticleModel.h"
#include "ui_mainwindow.h"

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

}
