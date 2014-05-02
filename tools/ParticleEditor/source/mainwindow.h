#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "XML.h"

class ParticleModel;
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
    void setParticleModel (ParticleModel* model);
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

    /** End events of changes in the gui **/

private:

    // The window
    Ui::MainWindow *ui;

    // The particle model
    ParticleModel* model;

    XML xml;

	IrrDisplay* irrDisplay;

};

#endif // MAINWINDOW_H
