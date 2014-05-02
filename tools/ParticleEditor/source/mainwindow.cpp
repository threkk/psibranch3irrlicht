#include <iostream>

#include <QFileDialog>
#include <QString>
#include <QColorDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

#include <ParticleModel.h>
#include <ParticleParser.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "XML.h"
#include "Util.h"
#include "IrrDisplay.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	irrDisplay = nullptr;
    ui->setupUi(this);
}

void MainWindow::setParticleModel(ParticleModel* model)
{
    this->model = model;
    fillFields(model);
	if (irrDisplay != nullptr) {
		irrDisplay->displayParticle(model);
	}
}

void MainWindow::setIrrDisplay (IrrDisplay* irrDisplay)
{
    this->irrDisplay = irrDisplay;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_name_textChanged(const QString &arg1)
{
    // TODO
}

/**
 * @brief MainWindow::fillFields, fill fields of the gui with the values from the Particle Model
 * @param model, Particle Model
 */
void MainWindow::fillFields (ParticleModel* model)
{
    QLineEdit* lineEdit_Direction_X = this->findChild<QLineEdit*>("lineEdit_Direction_X");
    lineEdit_Direction_X->setText(QString::number((double) model->getDirection().X));

    QLineEdit* lineEdit_Direction_Y = this->findChild<QLineEdit*>("lineEdit_Direction_Y");
    lineEdit_Direction_Y->setText(QString::number((double) model->getDirection().Y));

    QLineEdit* lineEdit_Direction_Z = this->findChild<QLineEdit*>("lineEdit_Direction_Z");
    lineEdit_Direction_Z->setText(QString::number((double) model->getDirection().Z));

    QPushButton* pushButton_Color_Min = this->findChild<QPushButton*>("pushButton_Color_Min");
    setButtonColor (pushButton_Color_Min, Util::SColorToQColor(model->getMinStartColor()));

    QPushButton* pushButton_Color_Max = this->findChild<QPushButton*>("pushButton_Color_Max");
    setButtonColor (pushButton_Color_Max, Util::SColorToQColor(model->getMaxStartColor()));

    QLineEdit* lineEdit_Angle = this->findChild<QLineEdit*>("lineEdit_Angle");
    lineEdit_Angle->setText(QString::number((double) model->getMaxAngleDegrees()));

    QLineEdit* lineEdit_Lifetime_Min = this->findChild<QLineEdit*>("lineEdit_Lifetime_Min");
    lineEdit_Lifetime_Min->setText(QString::number((double) model->getLifeTimeMin()));

    QLineEdit* lineEdit_Lifetime_Max = this->findChild<QLineEdit*>("lineEdit_Lifetime_Max");
    lineEdit_Lifetime_Max->setText(QString::number((double) model->getLifeTimeMax()));

    QLineEdit* lineEdit_PPS_Min = this->findChild<QLineEdit*>("lineEdit_PPS_Min");
    lineEdit_PPS_Min->setText(QString::number((double) model->getMinPPS()));

    QLineEdit* lineEdit_PPS_Max = this->findChild<QLineEdit*>("lineEdit_PPS_Max");
    lineEdit_PPS_Max->setText(QString::number((double) model->getMaxPPS()));

    QLineEdit* lineEdit_MinStartSize_X = this->findChild<QLineEdit*>("lineEdit_MinStartSize_X");
    lineEdit_MinStartSize_X->setText(QString::number((double) model->getMinStartSize().Width));

    QLineEdit* lineEdit_MinStartSize_Y = this->findChild<QLineEdit*>("lineEdit_MinStartSize_Y");
    lineEdit_MinStartSize_Y->setText(QString::number((double) model->getMinStartSize().Height));

    QLineEdit* lineEdit_MaxStartSize_X = this->findChild<QLineEdit*>("lineEdit_MaxStartSize_X");
    lineEdit_MaxStartSize_X->setText(QString::number((double) model->getMaxStartSize().Width));

    QLineEdit* lineEdit_MaxStartSize_Y = this->findChild<QLineEdit*>("lineEdit_MaxStartSize_Y");
    lineEdit_MaxStartSize_Y->setText(QString::number((double) model->getMaxStartSize().Height));

    QComboBox* comboBox_EmitterType = this->findChild<QComboBox*>("comboBox_EmitterType");
    comboBox_EmitterType->setCurrentIndex((int) model->getEmitterType());

    QFileInfo fileInfo(model->getPathNameTexture().c_str());
	QPushButton* pushButtonOpenText = this->findChild<QPushButton*>("pushButton_OpenTex");
	if (pushButtonOpenText != nullptr)
		pushButtonOpenText->setText(fileInfo.fileName());
}

void MainWindow::on_actionSave_XML_triggered()
{
    std::cout << "Save to xml: " << std::endl;
    XML xml;
    xml.SaveXML(model);
}

void MainWindow::on_actionOpen_XML_triggered()
{
    std::cout << "Open xml: " << std::endl;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",  tr("Files (*.*)"));
	ParticleParser p = ParticleParser();
	ParticleModel model = p.parse(fileName.toStdString().c_str());
	this->setParticleModel(&model);
}

void MainWindow::setButtonColor (QPushButton* button, QColor color)
{
    QString style = "background-color: rgb(%1, %2, %3);border: 0;text-align:left;padding-left:5px;";
    button->setStyleSheet(style.arg(color.red()).arg(color.green()).arg(color.blue()));
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
    QColor color = QColorDialog::getColor(QColor( model->getMinStartColor().getRed(), model->getMinStartColor().getGreen(), model->getMinStartColor().getBlue(), model->getMinStartColor().getAlpha()));

    QPushButton* button = this->findChild<QPushButton*>("pushButton_Color_Min");
    setButtonColor (button, color);

    model->setMinColor(Util::QColorToSColor(color));

    std::cout << "Change of min color: " << model->getMinStartColor().getAlpha() << ", " << model->getMinStartColor().getRed() << ", " << model->getMinStartColor().getBlue() << ", " << model->getMinStartColor().getGreen() << std::endl;
}

void MainWindow::on_pushButton_Color_Max_clicked()
{
    QColor color = QColorDialog::getColor(Qt::green);

    QPushButton* button = this->findChild<QPushButton*>("pushButton_Color_Max");
    setButtonColor (button, color);

    model->setMaxColor(Util::QColorToSColor(color));

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

void MainWindow::on_pushButton_OpenTex_clicked()
{
    //Open Texture
    QString texture = QFileDialog::getOpenFileName(this, tr("Open Texture File"),".",tr("Images (*.png *.xpm *.jpg *.bmp)"));
    if ( texture.isEmpty() )
        return;

    //Set name of the texture in the button name
    QFileInfo fileInfo(texture);
    QPushButton* pushButtonOpenText = this->findChild<QPushButton*>("pushButton_OpenTex");
	if (pushButtonOpenText != nullptr)
		pushButtonOpenText->setText(fileInfo.fileName());

    //Set the full path in the Particle Model
    model->setPathNameTexture(texture.toUtf8().constData());
}
