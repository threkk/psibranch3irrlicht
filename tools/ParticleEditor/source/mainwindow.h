#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "XML.h"
#include <ParticleModel.h>

class IrrDisplay;

namespace Ui {
class MainWindow;
}

class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setParticleModel (ParticleModel model);
	void setIrrDisplay (IrrDisplay* irrDisplay);
    ~MainWindow();

private slots:

    void fillFields (ParticleModel* model);

    // TODO: save the name of the model when this changes
    void on_lineEdit_name_textChanged(const QString &arg1);

    // On click of the save xml menu item
    void on_actionSave_XML_triggered();

	void on_actionOpen_XML_triggered();

    void setButtonColor (QPushButton* button, QColor color);

    /** Events for changes of values in the gui **/

    void on_lineEdit_Direction_X_textChanged(const QString &arg1);

    void on_lineEdit_Direction_Y_textChanged(const QString &arg1);

    void on_lineEdit_Direction_Z_textChanged(const QString &arg1);

    void on_pushButton_Color_Min_clicked();

    void on_pushButton_Color_Max_clicked();

    void on_lineEdit_Angle_textChanged(const QString &arg1);

    void on_lineEdit_Lifetime_Min_textChanged(const QString &arg1);

    void on_lineEdit_Lifetime_Max_textChanged(const QString &arg1);

    void on_lineEdit_PPS_Min_textChanged(const QString &arg1);

    void on_lineEdit_PPS_Max_textChanged(const QString &arg1);

    void on_lineEdit_MinStartSize_X_textChanged(const QString &arg1);

    void on_lineEdit_MinStartSize_Y_textChanged(const QString &arg1);

    void on_lineEdit_MaxStartSize_X_textChanged(const QString &arg1);

    void on_lineEdit_MaxStartSize_Y_textChanged(const QString &arg1);

    void on_comboBox_EmitterType_currentIndexChanged(int index);

    void on_pushButton_OpenTex_clicked();

	void on_lineEdit_Center_X_textChanged(const QString &arg1);

    void on_lineEdit_Center_Y_textChanged(const QString &arg1);

    void on_lineEdit_Center_Z_textChanged(const QString &arg1);

	void on_lineEdit_RingThickness_textChanged(const QString &arg1);

	void on_lineEdit_Radius_textChanged(const QString &arg1);

	void on_lineEdit_CylinderLength_textChanged(const QString &arg1);

	void on_checkBox_OutlineOnly_clicked(const bool &arg1);

	void on_lineEdit_StopEmittingAfter_textChanged(const QString &arg1);

	void on_lineEdit_RemoveAffectAfter_textChanged(const QString &arg1);

	void on_checkBox_Attract_Affector_clicked(const bool &arg1);

	void on_lineEdit_Attract_Point_X_textChanged(const QString &arg1);

	void on_lineEdit_Attract_Point_Y_textChanged(const QString &arg1);

	void on_lineEdit_Attract_Point_Z_textChanged(const QString &arg1);

	void on_lineEdit_Speed_textChanged(const QString &arg1);

	void on_checkBox_Attract_clicked(const bool &arg1);

	void on_checkBox_AffectX_clicked(const bool &arg1);

	void on_checkBox_AffectY_clicked(const bool &arg1);

	void on_checkBox_AffectZ_clicked(const bool &arg1);

	void on_checkBox_Fade_out_clicked(const bool &arg1);

	void on_pushButton_Target_Color_clicked();

	void on_lineEdit_Fade_Out_Time_textChanged(const QString &arg1);

	void on_checkBox_Gravity_clicked(const bool &arg1);

	void on_lineEdit_Gravity_X_textChanged(const QString &arg1);

	void on_lineEdit_Gravity_Y_textChanged(const QString &arg1);

	void on_lineEdit_Gravity_Z_textChanged(const QString &arg1);

	void on_lineEdit_Time_force_lost_textChanged(const QString &arg1);

	void on_checkBox_Rotate_clicked(const bool &arg1);

	void on_lineEdit_Speed_X_textChanged(const QString &arg1);

	void on_lineEdit_Speed_Y_textChanged(const QString &arg1);

	void on_lineEdit_Speed_Z_textChanged(const QString &arg1);

	void on_lineEdit_Pivot_Point_X_textChanged(const QString &arg1);

	void on_lineEdit_Pivot_Point_Y_textChanged(const QString &arg1);

	void on_lineEdit_Pivot_Point_Z_textChanged(const QString &arg1);

	void on_checkBox_Scale_clicked(const bool &arg1);

	void on_lineEdit_Scale_to_X_textChanged(const QString &arg1);

	void on_lineEdit_Scale_to_Y_textChanged(const QString &arg1);

	void on_lineEdit_Normal_X_textChanged(const QString &arg1);

	void on_lineEdit_Normal_Y_textChanged(const QString &arg1);

	void on_lineEdit_Normal_Z_textChanged(const QString &arg1);

	void on_lineEdit_Aabbox_Width_textChanged(const QString &arg1);

	void on_lineEdit_Aabbox_Height_textChanged(const QString &arg1);

	void on_lineEdit_Aabbox_Depth_textChanged(const QString &arg1);

	void on_comboBox_MaterialType_currentIndexChanged(int index);

    /** End events of changes in the gui **/

private:

    // The window
    Ui::MainWindow *ui;

    // The particle model
    ParticleModel model;

    XML xml;

	IrrDisplay* irrDisplay;

};

#endif // MAINWINDOW_H
