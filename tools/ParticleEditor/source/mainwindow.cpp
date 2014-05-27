#include <iostream>

#include <QFileDialog>
#include <QString>
#include <QColorDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>

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

void MainWindow::setParticleModel(ParticleModel model)
{
    this->model = model;
    fillFields(&model);
	if (irrDisplay != nullptr) {
		irrDisplay->displayParticle(&model);
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

	QLineEdit* lineEdit_Center_X = this->findChild<QLineEdit*>("lineEdit_Center_X");
    lineEdit_Center_X->setText(QString::number((double) model->getCenter().X));

    QLineEdit* lineEdit_Center_Y = this->findChild<QLineEdit*>("lineEdit_Center_Y");
    lineEdit_Center_Y->setText(QString::number((double) model->getCenter().Y));

    QLineEdit* lineEdit_Center_Z = this->findChild<QLineEdit*>("lineEdit_Center_Z");
    lineEdit_Center_Z->setText(QString::number((double) model->getCenter().Z));

	QLineEdit* lineEdit_Center_X_2 = this->findChild<QLineEdit*>("lineEdit_Center_X_2");
    lineEdit_Center_X->setText(QString::number((double) model->getCenter().X));

    QLineEdit* lineEdit_Center_Y_2 = this->findChild<QLineEdit*>("lineEdit_Center_Y_2");
    lineEdit_Center_Y->setText(QString::number((double) model->getCenter().Y));

    QLineEdit* lineEdit_Center_Z_2 = this->findChild<QLineEdit*>("lineEdit_Center_Z_2");
    lineEdit_Center_Z->setText(QString::number((double) model->getCenter().Z));

	QLineEdit* lineEdit_Center_X_3 = this->findChild<QLineEdit*>("lineEdit_Center_X_3");
    lineEdit_Center_X->setText(QString::number((double) model->getCenter().X));

    QLineEdit* lineEdit_Center_Y_3 = this->findChild<QLineEdit*>("lineEdit_Center_Y_3");
    lineEdit_Center_Y->setText(QString::number((double) model->getCenter().Y));

    QLineEdit* lineEdit_Center_Z_3 = this->findChild<QLineEdit*>("lineEdit_Center_Z_3");
    lineEdit_Center_Z->setText(QString::number((double) model->getCenter().Z));

	QLineEdit* lineEdit_RingThickness = this->findChild<QLineEdit*>("lineEdit_RingThickness");
	lineEdit_RingThickness->setText(QString::number((double) model->getRingThickness()));

	QLineEdit* lineEdit_Radius = this->findChild<QLineEdit*>("lineEdit_Radius");
	lineEdit_Radius->setText(QString::number((double) model->getRadius()));

	QLineEdit* lineEdit_Radius_2 = this->findChild<QLineEdit*>("lineEdit_Radius_2");
	lineEdit_Radius->setText(QString::number((double) model->getRadius()));

	QLineEdit* lineEdit_CylinderLength = this->findChild<QLineEdit*>("lineEdit_CylinderLength");
	lineEdit_CylinderLength->setText(QString::number((double) model->getLengthCylinder()));

	QCheckBox* checkBox_OutlineOnly = this->findChild<QCheckBox*>("checkBox_OutlineOnly");
	checkBox_OutlineOnly->setChecked(model->getOutLineOnly());

	QLineEdit* lineEdit_StopEmittingAfter = this->findChild<QLineEdit*>("lineEdit_StopEmittingAfter");
	lineEdit_StopEmittingAfter->setText(QString::number((double) model->getStopEmitting()));

	QLineEdit* lineEdit_RemoveAffectAfter = this->findChild<QLineEdit*>("lineEdit_RemoveAffectAfter");
	lineEdit_RemoveAffectAfter->setText(QString::number((double) model->getRemoveParticleAfter()));

    QFileInfo fileInfo(model->getPathNameTexture().c_str());
	QPushButton* pushButtonOpenText = this->findChild<QPushButton*>("pushButton_OpenTex");
	if (pushButtonOpenText != nullptr)
		pushButtonOpenText->setText(fileInfo.fileName());
	
	//Affectors
	QCheckBox* checkBox_Attract_Affector = this->findChild<QCheckBox*>("checkBox_Attract_Affector");
	checkBox_Attract_Affector->setChecked(model->hasAffector(ParticleModel::AffectorTypes::ATTRACT));

	QLineEdit* lineEdit_Attract_Point_X = this->findChild<QLineEdit*>("lineEdit_Attract_Point_X");
	lineEdit_Attract_Point_X->setText(QString::number((double) model->getAttractionAffectorPoint().X));

	QLineEdit* lineEdit_Attract_Point_Y = this->findChild<QLineEdit*>("lineEdit_Attract_Point_Y");
	lineEdit_Attract_Point_Y->setText(QString::number((double) model->getAttractionAffectorPoint().Y));

	QLineEdit* lineEdit_Attract_Point_Z = this->findChild<QLineEdit*>("lineEdit_Attract_Point_Z");
	lineEdit_Attract_Point_Z->setText(QString::number((double) model->getAttractionAffectorPoint().Z));

	QLineEdit* lineEdit_Speed = this->findChild<QLineEdit*>("lineEdit_Speed");
	lineEdit_Speed->setText(QString::number((double) model->getAttractionAffectorSpeed()));

	QCheckBox* checkBox_Attract = this->findChild<QCheckBox*>("checkBox_Attract");
	checkBox_Attract->setChecked(model->getAttractionAffectorAttract());

	QCheckBox* checkBox_AffectX = this->findChild<QCheckBox*>("checkBox_AffectX");
	checkBox_AffectX->setChecked(model->getAttractionAffectorAffectX());

	QCheckBox* checkBox_AffectY = this->findChild<QCheckBox*>("checkBox_AffectY");
	checkBox_AffectY->setChecked(model->getAttractionAffectorAffectY());

	QCheckBox* checkBox_AffectZ = this->findChild<QCheckBox*>("checkBox_AffectZ");
	checkBox_AffectZ->setChecked(model->getAttractionAffectorAffectZ());

	QCheckBox* checkBox_Fade_out = this->findChild<QCheckBox*>("checkBox_Fade_out");
	checkBox_Fade_out->setChecked(model->hasAffector(ParticleModel::AffectorTypes::FADE_OUT));

	QPushButton* pushButton_Target_Color = this->findChild<QPushButton*>("pushButton_Target_Color");
	setButtonColor (pushButton_Target_Color, Util::SColorToQColor(model->getFadeOutAffectorTargetColor()));

	QLineEdit* lineEdit_Fade_Out_Time = this->findChild<QLineEdit*>("lineEdit_Fade_Out_Time");
	lineEdit_Fade_Out_Time->setText(QString::number((double) model->getFadeOutAffectorTimeNeededToFadeOut()));

	QCheckBox* checkBox_Gravity = this->findChild<QCheckBox*>("checkBox_Gravity");
	checkBox_Gravity->setChecked(model->hasAffector(ParticleModel::AffectorTypes::GRAVITY));

	QLineEdit* lineEdit_Gravity_X = this->findChild<QLineEdit*>("lineEdit_Gravity_X");
	lineEdit_Gravity_X->setText(QString::number((double) model->getGravityAffectorGravity().X));

	QLineEdit* lineEdit_Gravity_Y = this->findChild<QLineEdit*>("lineEdit_Gravity_Y");
	lineEdit_Gravity_Y->setText(QString::number((double) model->getGravityAffectorGravity().Y));

	QLineEdit* lineEdit_Gravity_Z = this->findChild<QLineEdit*>("lineEdit_Gravity_Z");
	lineEdit_Gravity_Z->setText(QString::number((double) model->getGravityAffectorGravity().Z));

	QLineEdit* lineEdit_Time_force_lost = this->findChild<QLineEdit*>("lineEdit_Time_force_lost");
	lineEdit_Time_force_lost->setText(QString::number((double) model->getGravityAffectorTimeForceLost()));

	QCheckBox* checkBox_Rotate = this->findChild<QCheckBox*>("checkBox_Rotate");
	checkBox_Rotate->setChecked(model->hasAffector(ParticleModel::AffectorTypes::ROTATE));

	QLineEdit* lineEdit_Speed_X = this->findChild<QLineEdit*>("lineEdit_Speed_X");
	lineEdit_Speed_X->setText(QString::number((double) model->getRotationAffectorSpeed().X));

	QLineEdit* lineEdit_Speed_Y = this->findChild<QLineEdit*>("lineEdit_Speed_Y");
	lineEdit_Speed_Y->setText(QString::number((double) model->getRotationAffectorSpeed().Y));

	QLineEdit* lineEdit_Speed_Z = this->findChild<QLineEdit*>("lineEdit_Speed_Z");
	lineEdit_Speed_Z->setText(QString::number((double) model->getRotationAffectorSpeed().Z));

	QLineEdit* lineEdit_Pivot_Point_X = this->findChild<QLineEdit*>("lineEdit_Pivot_Point_X");
	lineEdit_Pivot_Point_X->setText(QString::number((double) model->getRotationAffectorPivotPoint().X));

	QLineEdit* lineEdit_Pivot_Point_Y = this->findChild<QLineEdit*>("lineEdit_Pivot_Point_Y");
	lineEdit_Pivot_Point_Y->setText(QString::number((double) model->getRotationAffectorPivotPoint().Y));

	QLineEdit* lineEdit_Pivot_Point_Z = this->findChild<QLineEdit*>("lineEdit_Pivot_Point_Z");
	lineEdit_Pivot_Point_Z->setText(QString::number((double) model->getRotationAffectorPivotPoint().Z));

	QCheckBox* checkBox_Scale = this->findChild<QCheckBox*>("checkBox_Scale");
	checkBox_Scale->setChecked(model->hasAffector(ParticleModel::AffectorTypes::SCALE));

	QLineEdit* lineEdit_Scale_to_X = this->findChild<QLineEdit*>("lineEdit_Scale_to_X");
	lineEdit_Scale_to_X->setText(QString::number((double) model->getScaleAffectorScaleTo().Width));

	QLineEdit* lineEdit_Scale_to_Y = this->findChild<QLineEdit*>("lineEdit_Scale_to_Y");
	lineEdit_Scale_to_Y->setText(QString::number((double) model->getScaleAffectorScaleTo().Height));

	QLineEdit* lineEdit_Normal_X = this->findChild<QLineEdit*>("lineEdit_Normal_X");
	lineEdit_Normal_X->setText(QString::number((double) model->getNormal().X));

	QLineEdit* lineEdit_Normal_Y = this->findChild<QLineEdit*>("lineEdit_Normal_Y");
	lineEdit_Normal_Y->setText(QString::number((double) model->getNormal().Y));

	QLineEdit* lineEdit_Normal_Z = this->findChild<QLineEdit*>("lineEdit_Normal_Z");
	lineEdit_Normal_Z->setText(QString::number((double) model->getNormal().Z));

	QLineEdit* lineEdit_Aabbox_Width = this->findChild<QLineEdit*>("lineEdit_Aabbox_Width");
	lineEdit_Aabbox_Width->setText(QString::number((double) model->getAabbox().MaxEdge.X * 2));

	QLineEdit* lineEdit_Aabbox_Height = this->findChild<QLineEdit*>("lineEdit_Aabbox_Height");
	lineEdit_Aabbox_Height->setText(QString::number((double) model->getAabbox().MaxEdge.Y * 2));

	QLineEdit* lineEdit_Aabbox_Depth = this->findChild<QLineEdit*>("lineEdit_Aabbox_Depth");
	lineEdit_Aabbox_Depth->setText(QString::number((double) model->getAabbox().MaxEdge.Z * 2));

	QComboBox* comboBox_MaterialType = this->findChild<QComboBox*>("comboBox_MaterialType");
    comboBox_MaterialType->setCurrentIndex((int) model->getMaterialType());

	if (model->getEmitterType() == 1)
	{
		QScrollArea* area = this->findChild<QScrollArea*>("scrollArea");
		area->hide();

		QScrollArea* area2 = this->findChild<QScrollArea*>("scrollArea_2");
		area2->hide();

		QScrollArea* area5 = this->findChild<QScrollArea*>("scrollArea_5");
		area5->hide();

		QScrollArea* area3 = this->findChild<QScrollArea*>("scrollArea_3");
		area3->show();
	}

}

void MainWindow::on_actionSave_XML_triggered()
{
    std::cout << "Save to xml: " << std::endl;
    XML xml;
    xml.SaveXML(&model);
}

void MainWindow::on_actionOpen_XML_triggered()
{
    std::cout << "Open xml: " << std::endl;
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",  tr("Files (*.*)"));
	ParticleParser p = ParticleParser();
	ParticleModel model = p.parse(fileName.toStdString().c_str());
	this->setParticleModel(model);
}

void MainWindow::setButtonColor (QPushButton* button, QColor color)
{
    QString style = "background-color: rgb(%1, %2, %3);border: 0;text-align:left;padding-left:5px;";
    button->setStyleSheet(style.arg(color.red()).arg(color.green()).arg(color.blue()));
}

void MainWindow::on_lineEdit_Direction_X_textChanged(const QString &arg1)
{
    model.setDirection(core::vector3df (arg1.toFloat(), model.getDirection().Y, model.getDirection().Z));
    std::cout << "Change of direction: " << model.getDirection().X << ", " << model.getDirection().Y << ", " << model.getDirection().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Direction_Y_textChanged(const QString &arg1)
{
    model.setDirection(core::vector3df (model.getDirection().X, arg1.toFloat(), model.getDirection().Z));
    std::cout << "Change of direction: " << model.getDirection().X << ", " << model.getDirection().Y << ", " << model.getDirection().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Direction_Z_textChanged(const QString &arg1)
{
    model.setDirection(core::vector3df (model.getDirection().X, model.getDirection().Y, arg1.toFloat()));
    std::cout << "Change of direction: " << model.getDirection().X << ", " << model.getDirection().Y << ", " << model.getDirection().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_pushButton_Color_Min_clicked()
{
	QColor color = QColorDialog::getColor(QColor( model.getMinStartColor().getRed(), model.getMinStartColor().getGreen(), model.getMinStartColor().getBlue(), model.getMinStartColor().getAlpha()), 0, "Min start color", QColorDialog::ShowAlphaChannel);

    QPushButton* button = this->findChild<QPushButton*>("pushButton_Color_Min");
    setButtonColor (button, color);

    model.setMinColor(Util::QColorToSColor(color));

    std::cout << "Change of min color: " << model.getMinStartColor().getAlpha() << ", " << model.getMinStartColor().getRed() << ", " << model.getMinStartColor().getBlue() << ", " << model.getMinStartColor().getGreen() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_pushButton_Color_Max_clicked()
{
	QColor color = QColorDialog::getColor(QColor( model.getMaxStartColor().getRed(), model.getMaxStartColor().getGreen(), model.getMaxStartColor().getBlue(), model.getMaxStartColor().getAlpha()), 0, "Max start color", QColorDialog::ShowAlphaChannel);

    QPushButton* button = this->findChild<QPushButton*>("pushButton_Color_Max");
    setButtonColor (button, color);

    model.setMaxColor(Util::QColorToSColor(color));

    std::cout << "Change of max color: " << model.getMaxStartColor().getAlpha() << ", " << model.getMaxStartColor().getRed() << ", " << model.getMaxStartColor().getBlue() << ", " << model.getMaxStartColor().getGreen() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Angle_textChanged(const QString &arg1)
{
    model.setMaxAngleDegrees(arg1.toFloat());
    std::cout << "Change of angle: " << model.getMaxAngleDegrees() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Lifetime_Min_textChanged(const QString &arg1)
{
    model.setLifeTimeMin(arg1.toFloat());
    std::cout << "Change of min life time: " << model.getLifeTimeMin() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Lifetime_Max_textChanged(const QString &arg1)
{
    model.setLifeTimeMax(arg1.toFloat());
    std::cout << "Change of max life time: " << model.getLifeTimeMax() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_PPS_Min_textChanged(const QString &arg1)
{
    model.setMinPPS(arg1.toFloat());
    std::cout << "Change of min pps: " << model.getMinPPS() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_PPS_Max_textChanged(const QString &arg1)
{
    model.setMaxPPS(arg1.toFloat());
    std::cout << "Change of max pps: " << model.getMaxPPS() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_MinStartSize_X_textChanged(const QString &arg1)
{
    model.setMinStartSize(core::dimension2df(arg1.toFloat(), model.getMinStartSize().Height));
    std::cout << "Change of min start size: " << model.getMinStartSize().Width << ", " << model.getMinStartSize().Height << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_MinStartSize_Y_textChanged(const QString &arg1)
{
    model.setMinStartSize(core::dimension2df(model.getMinStartSize().Width, arg1.toFloat()));
    std::cout << "Change of min start size: " << model.getMinStartSize().Width << ", " << model.getMinStartSize().Height << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_MaxStartSize_X_textChanged(const QString &arg1)
{
    model.setMaxStartSize(core::dimension2df(arg1.toFloat(), model.getMaxStartSize().Height));
    std::cout << "Change of max start size: " << model.getMaxStartSize().Width << ", " << model.getMaxStartSize().Height << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_MaxStartSize_Y_textChanged(const QString &arg1)
{
    model.setMaxStartSize(core::dimension2df(model.getMaxStartSize().Width, arg1.toFloat()));
    std::cout << "Change of max start size: " << model.getMaxStartSize().Width << ", " << model.getMaxStartSize().Height << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_comboBox_EmitterType_currentIndexChanged(int index)
{
    model.setEmitterType(static_cast<ParticleModel::EmitterTypes>(index));
    std::cout << "Change of emitter type: " << model.getEmitterType() << std::endl;
	irrDisplay->displayParticle(&model);
	
			if (model.getEmitterType() == 0)
	{
		QScrollArea* area = this->findChild<QScrollArea*>("scrollArea");
		area->hide();

		QScrollArea* area2 = this->findChild<QScrollArea*>("scrollArea_2");
		area2->hide();

		QScrollArea* area5 = this->findChild<QScrollArea*>("scrollArea_5");
		area5->hide();

		QScrollArea* area3 = this->findChild<QScrollArea*>("scrollArea_3");
		area3->hide();
	}
		else if (model.getEmitterType() == 1)
		{
			QScrollArea* area = this->findChild<QScrollArea*>("scrollArea");
		area->hide();

		QScrollArea* area2 = this->findChild<QScrollArea*>("scrollArea_2");
		area2->hide();

		QScrollArea* area5 = this->findChild<QScrollArea*>("scrollArea_5");
		area5->hide();

		QScrollArea* area3 = this->findChild<QScrollArea*>("scrollArea_3");
		area3->show();

			} else if (model.getEmitterType() == 2)
	{
		QScrollArea* area = this->findChild<QScrollArea*>("scrollArea");
		area->hide();

		QScrollArea* area2 = this->findChild<QScrollArea*>("scrollArea_2");
		area2->hide();

		QScrollArea* area5 = this->findChild<QScrollArea*>("scrollArea_5");
		area5->hide();

		QScrollArea* area3 = this->findChild<QScrollArea*>("scrollArea_3");
		area3->hide();
	} 	else if (model.getEmitterType() == 3)
	{
		QScrollArea* area2 = this->findChild<QScrollArea*>("scrollArea_2");
		area2->hide();

		QScrollArea* area5 = this->findChild<QScrollArea*>("scrollArea_5");
		area5->hide();

		QScrollArea* area3 = this->findChild<QScrollArea*>("scrollArea_3");
		area3->hide();

		QScrollArea* area = this->findChild<QScrollArea*>("scrollArea");
		area->show();

	} else if (model.getEmitterType() == 4)
	{
		QScrollArea* area = this->findChild<QScrollArea*>("scrollArea");
		area->hide();

		QScrollArea* area5 = this->findChild<QScrollArea*>("scrollArea_5");
		area5->hide();

		QScrollArea* area3 = this->findChild<QScrollArea*>("scrollArea_3");
		area3->hide();

		QScrollArea* area2 = this->findChild<QScrollArea*>("scrollArea_2");
		area2->show();

	} else 
	{
		QScrollArea* area = this->findChild<QScrollArea*>("scrollArea");
		area->hide();

		QScrollArea* area2 = this->findChild<QScrollArea*>("scrollArea_2");
		area2->hide();

		QScrollArea* area3 = this->findChild<QScrollArea*>("scrollArea_3");
		area3->hide();

		QScrollArea* area5 = this->findChild<QScrollArea*>("scrollArea_5");
		area5->show();
	}
}

void MainWindow::on_lineEdit_Center_X_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (arg1.toFloat(), model.getCenter().Y, model.getCenter().Z));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Center_Y_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (model.getCenter().X, arg1.toFloat(), model.getCenter().Z));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Center_Z_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (model.getCenter().X, model.getCenter().Y, arg1.toFloat()));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Center_X_2_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (arg1.toFloat(), model.getCenter().Y, model.getCenter().Z));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Center_Y_2_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (model.getCenter().X, arg1.toFloat(), model.getCenter().Z));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Center_Z_2_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (model.getCenter().X, model.getCenter().Y, arg1.toFloat()));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Center_X_3_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (arg1.toFloat(), model.getCenter().Y, model.getCenter().Z));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Center_Y_3_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (model.getCenter().X, arg1.toFloat(), model.getCenter().Z));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Center_Z_3_textChanged(const QString &arg1)
{
    model.setCenter(core::vector3df (model.getCenter().X, model.getCenter().Y, arg1.toFloat()));
    std::cout << "Change of center: " << model.getCenter().X << ", " << model.getCenter().Y << ", " << model.getCenter().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_RingThickness_textChanged(const QString &arg1)
{
	model.setRingThickness(arg1.toFloat());
	std::cout << "Change of ring thickness: " << model.getRingThickness() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Radius_textChanged(const QString &arg1)
{
	model.setRadius(arg1.toFloat());
	std::cout << "Change of radius: " << model.getRadius() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Radius_2_textChanged(const QString &arg1)
{
	model.setRadius(arg1.toFloat());
	std::cout << "Change of radius: " << model.getRadius() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_CylinderLength_textChanged(const QString &arg1)
{
	model.setLengthCylinder(arg1.toFloat());
	std::cout << "Change of cylinder length: " << model.getLengthCylinder() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_OutlineOnly_clicked(const bool &arg1)
{
	model.setOutLineOnly(arg1);
	std::cout << "Change of outline only: " << model.getOutLineOnly() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_StopEmittingAfter_textChanged(const QString & arg1)
{
	model.setStopEmitting(arg1.toFloat());
	std::cout << "Change of Stop emitting: " << model.getStopEmitting() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_RemoveAffectAfter_textChanged(const QString & arg1)
{
	model.setRemoveParticleAfter(arg1.toFloat());
	std::cout << "Change of Remove After: " << model.getRemoveParticleAfter() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_Attract_Affector_clicked(const bool &arg1)
{
	if(arg1 == true)
	{
		model.addAffectorType(ParticleModel::AffectorTypes::ATTRACT);
	}
	if(arg1 == false)
	{ 
		model.removeAffectorType(ParticleModel::AffectorTypes::ATTRACT);
	}
	std::cout << "Change of affectorType: " << model.getAffectors() << std::endl;
	std::cout << "Change of boolean " << arg1 << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Attract_Point_X_textChanged(const QString &arg1)
{
	model.setAttractionAffectorPoint(core::vector3df(arg1.toFloat(), model.getAttractionAffectorPoint().Y, model.getAttractionAffectorPoint().Z));
	std::cout << "Change of center: " << model.getAttractionAffectorPoint().X << ", " << model.getAttractionAffectorPoint().Y
		<< ", " << model.getAttractionAffectorPoint().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Attract_Point_Y_textChanged(const QString &arg1)
{
	model.setAttractionAffectorPoint(core::vector3df(model.getAttractionAffectorPoint().X, arg1.toFloat(), model.getAttractionAffectorPoint().Z));
	std::cout << "Change of center: " << model.getAttractionAffectorPoint().X << ", " << model.getAttractionAffectorPoint().Y
		<< ", " << model.getAttractionAffectorPoint().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Attract_Point_Z_textChanged(const QString &arg1)
{
	model.setAttractionAffectorPoint(core::vector3df(model.getAttractionAffectorPoint().X, model.getAttractionAffectorPoint().Y, arg1.toFloat()));
	std::cout << "Change of center: " << model.getAttractionAffectorPoint().X << ", " << model.getAttractionAffectorPoint().Y
		<< ", " << model.getAttractionAffectorPoint().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Speed_textChanged(const QString &arg1)
{
	model.setAttractionAffectorSpeed(arg1.toFloat());
	std::cout << "Change of attract speed: " << model.getAttractionAffectorSpeed() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_Attract_clicked(const bool &arg1)
{
	model.setAttractionAffectorAttract(arg1);
	std::cout << "Change of attract boolean: " << model.getAttractionAffectorAttract() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_AffectX_clicked(const bool &arg1)
{
	model.setAttractionAffectorAffectX(arg1);
	std::cout << "Change of attraction affect X: " << model.getAttractionAffectorAffectX() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_AffectY_clicked(const bool &arg1)
{
	model.setAttractionAffectorAffectY(arg1);
	std::cout << "Change of attraction affect Y: " << model.getAttractionAffectorAffectY() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_AffectZ_clicked(const bool &arg1)
{
	model.setAttractionAffectorAffectZ(arg1);
	std::cout << "Change of attraction affect Z: " << model.getAttractionAffectorAffectZ() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_Fade_out_clicked(const bool &arg1)
{
	if(arg1 == true)
	{
		model.addAffectorType(ParticleModel::AffectorTypes::FADE_OUT);
	}
	if(arg1 == false)
	{ 
		model.removeAffectorType(ParticleModel::AffectorTypes::FADE_OUT);
	}
	std::cout << "Change of affectorType: " << model.getAffectors() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_pushButton_Target_Color_clicked()
{
	QColor color = QColorDialog::getColor(QColor( model.getFadeOutAffectorTargetColor().getRed(), model.getFadeOutAffectorTargetColor().getGreen(), model.getFadeOutAffectorTargetColor().getBlue(), model.getFadeOutAffectorTargetColor().getAlpha()), 0, "Fadeout target color", QColorDialog::ShowAlphaChannel);

    QPushButton* button = this->findChild<QPushButton*>("pushButton_Target_Color");
    setButtonColor (button, color);

    model.setFadeOutAffectorTargetColor(Util::QColorToSColor(color));

    std::cout << "Change of target color: " << model.getFadeOutAffectorTargetColor().getAlpha() << ", " << model.getFadeOutAffectorTargetColor().getRed() << ", " << model.getFadeOutAffectorTargetColor().getBlue() << ", " << model.getFadeOutAffectorTargetColor().getGreen() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Fade_Out_Time_textChanged(const QString &arg1)
{
	model.setFadeOutAffectorTimeNeededToFadeOut(arg1.toFloat());
	std::cout << "Change of time needed to fade out: " << model.getFadeOutAffectorTimeNeededToFadeOut() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_Gravity_clicked(const bool &arg1)
{
	if(arg1 == true)
	{
		model.addAffectorType(ParticleModel::AffectorTypes::GRAVITY);
	}
	if(arg1 == false)
	{ 
		model.removeAffectorType(ParticleModel::AffectorTypes::GRAVITY);
	}
	std::cout << "Change of affectorType: " << model.getAffectors() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Gravity_X_textChanged(const QString &arg1)
{
	model.setGravityAffectorGravity(core::vector3df(arg1.toFloat(), model.getGravityAffectorGravity().Y, model.getGravityAffectorGravity().Z));
	std::cout << "Change of center: " << model.getGravityAffectorGravity().X << ", " << model.getGravityAffectorGravity().Y
		<< ", " << model.getGravityAffectorGravity().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Gravity_Y_textChanged(const QString &arg1)
{
	model.setGravityAffectorGravity(core::vector3df(model.getGravityAffectorGravity().X, arg1.toFloat(), model.getGravityAffectorGravity().Z));
	std::cout << "Change of center: " << model.getGravityAffectorGravity().X << ", " << model.getGravityAffectorGravity().Y
		<< ", " << model.getGravityAffectorGravity().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Gravity_Z_textChanged(const QString &arg1)
{
	model.setGravityAffectorGravity(core::vector3df(model.getGravityAffectorGravity().X, model.getGravityAffectorGravity().Y, arg1.toFloat()));
	std::cout << "Change of center: " << model.getGravityAffectorGravity().X << ", " << model.getGravityAffectorGravity().Y
		<< ", " << model.getGravityAffectorGravity().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Time_force_lost_textChanged(const QString &arg1)
{
	model.setGravityAffectorTimeForceLost(arg1.toFloat());
	std::cout << "Change of time force lost: " << model.getGravityAffectorTimeForceLost() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_Rotate_clicked(const bool &arg1)
{
	if(arg1 == true)
	{
		model.addAffectorType(ParticleModel::AffectorTypes::ROTATE);
	}
	if(arg1 == false)
	{ 
		model.removeAffectorType(ParticleModel::AffectorTypes::ROTATE);
	}
	std::cout << "Change of affectorType: " << model.getAffectors() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Speed_X_textChanged(const QString &arg1)
{
	model.setRotationAffectorSpeed(core::vector3df(arg1.toFloat(), model.getRotationAffectorSpeed().Y, model.getRotationAffectorSpeed().Z));
	std::cout << "Change of center: " << model.getRotationAffectorSpeed().X << ", " << model.getRotationAffectorSpeed().Y
		<< ", " << model.getRotationAffectorSpeed().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Speed_Y_textChanged(const QString &arg1)
{
	model.setRotationAffectorSpeed(core::vector3df(model.getRotationAffectorSpeed().X, arg1.toFloat(), model.getRotationAffectorSpeed().Z));
	std::cout << "Change of center: " << model.getRotationAffectorSpeed().X << ", " << model.getRotationAffectorSpeed().Y
		<< ", " << model.getRotationAffectorSpeed().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Speed_Z_textChanged(const QString &arg1)
{
	model.setRotationAffectorSpeed(core::vector3df(model.getRotationAffectorSpeed().X, model.getRotationAffectorSpeed().Y, arg1.toFloat()));
	std::cout << "Change of center: " << model.getRotationAffectorSpeed().X << ", " << model.getRotationAffectorSpeed().Y
		<< ", " << model.getRotationAffectorSpeed().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Pivot_Point_X_textChanged(const QString &arg1)
{
	model.setRotationAffectorPivotPoint(core::vector3df(arg1.toFloat(), model.getRotationAffectorSpeed().Y, model.getRotationAffectorPivotPoint().Z));
	std::cout << "Change of center: " << model.getRotationAffectorPivotPoint().X << ", " << model.getRotationAffectorPivotPoint().Y
		<< ", " << model.getRotationAffectorPivotPoint().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Pivot_Point_Y_textChanged(const QString &arg1)
{
	model.setRotationAffectorSpeed(core::vector3df(model.getRotationAffectorSpeed().X, arg1.toFloat(), model.getRotationAffectorSpeed().Z ));
	std::cout << "Change of center: " << model.getRotationAffectorPivotPoint().X << ", " << model.getRotationAffectorPivotPoint().Y
		<< ", " << model.getRotationAffectorPivotPoint().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Pivot_Point_Z_textChanged(const QString &arg1)
{
	model.setRotationAffectorSpeed(core::vector3df(model.getRotationAffectorSpeed().X, model.getRotationAffectorSpeed().Y, arg1.toFloat()));
	std::cout << "Change of center: " << model.getRotationAffectorPivotPoint().X << ", " << model.getRotationAffectorPivotPoint().Y
		<< ", " << model.getRotationAffectorPivotPoint().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_checkBox_Scale_clicked(const bool &arg1)
{
	if(arg1 == true)
	{
		model.addAffectorType(ParticleModel::AffectorTypes::SCALE);
	}
	if(arg1 == false)
	{ 
		model.removeAffectorType(ParticleModel::AffectorTypes::SCALE);
	}
	std::cout << "Change of affectorType: " << model.getAffectors() << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Scale_to_X_textChanged(const QString &arg1)
{
	model.setScaleAffectorScaleTo(core::dimension2df(arg1.toFloat(), model.getScaleAffectorScaleTo().Height));
    std::cout << "Change of min scale size: " << model.getScaleAffectorScaleTo().Width << ", " << model.getScaleAffectorScaleTo().Height << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Scale_to_Y_textChanged(const QString &arg1)
{
	model.setScaleAffectorScaleTo(core::dimension2df(model.getScaleAffectorScaleTo().Width, arg1.toFloat()));
    std::cout << "Change of min scale size: " << model.getScaleAffectorScaleTo().Width << ", " << model.getScaleAffectorScaleTo().Height << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Normal_X_textChanged(const QString &arg1)
{
	model.setNormal(core::vector3df(arg1.toFloat(), model.getNormal().Y, model.getNormal().Z));
	std::cout << "Change of normal: " << model.getNormal().X << ", " << model.getNormal().Y
		<< ", " << model.getNormal().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Normal_Y_textChanged(const QString &arg1)
{
	model.setNormal(core::vector3df(model.getNormal().X, arg1.toFloat(), model.getNormal().Z ));
	std::cout << "Change of normal: " << model.getNormal().X << ", " << model.getNormal().Y
		<< ", " << model.getNormal().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Normal_Z_textChanged(const QString &arg1)
{
	model.setNormal(core::vector3df(model.getNormal().X, model.getNormal().Y, arg1.toFloat()));
	std::cout << "Change of normal: " << model.getNormal().X << ", " << model.getNormal().Y
		<< ", " << model.getNormal().Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Aabbox_Width_textChanged(const QString &arg1)
{
	model.setAabbox(core::aabbox3df(-arg1.toFloat()/2, model.getAabbox().MinEdge.Y, model.getAabbox().MinEdge.Z,
		arg1.toFloat()/2, model.getAabbox().MaxEdge.Y, model.getAabbox().MaxEdge.Z));
	std::cout << "Change of aabbox: " << model.getAabbox().MinEdge.X << ", " << model.getAabbox().MinEdge.Y << ", " << model.getAabbox().MinEdge.Z
		 << ", " << model.getAabbox().MaxEdge.X << ", " << model.getAabbox().MaxEdge.Y << ", " << model.getAabbox().MaxEdge.Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Aabbox_Height_textChanged(const QString &arg1)
{
	model.setAabbox(core::aabbox3df(model.getAabbox().MinEdge.X, -arg1.toFloat()/2, model.getAabbox().MinEdge.Z,
		model.getAabbox().MaxEdge.X, arg1.toFloat()/2, model.getAabbox().MaxEdge.Z));
	std::cout << "Change of aabbox: " << model.getAabbox().MinEdge.X << ", " << model.getAabbox().MinEdge.Y << ", " << model.getAabbox().MinEdge.Z
		 << ", " << model.getAabbox().MaxEdge.X << ", " << model.getAabbox().MaxEdge.Y << ", " << model.getAabbox().MaxEdge.Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_lineEdit_Aabbox_Depth_textChanged(const QString &arg1)
{
	model.setAabbox(core::aabbox3df(model.getAabbox().MinEdge.X, model.getAabbox().MinEdge.Y, -arg1.toFloat()/2,
		model.getAabbox().MaxEdge.X, model.getAabbox().MaxEdge.Y, arg1.toFloat()/2));
	std::cout << "Change of aabbox: " << model.getAabbox().MinEdge.X << ", " << model.getAabbox().MinEdge.Y << ", " << model.getAabbox().MinEdge.Z
		 << ", " << model.getAabbox().MaxEdge.X << ", " << model.getAabbox().MaxEdge.Y << ", " << model.getAabbox().MaxEdge.Z << std::endl;
	irrDisplay->displayParticle(&model);
}

void MainWindow::on_comboBox_MaterialType_currentIndexChanged(int index)
{
    model.setMaterialType(static_cast<ParticleModel::MaterialTypes>(index));
    std::cout << "Change of material type: " << model.getMaterialType() << std::endl;
	irrDisplay->displayParticle(&model);
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
    model.setPathNameTexture(texture.toUtf8().constData());

	irrDisplay->displayParticle(&model);
}
