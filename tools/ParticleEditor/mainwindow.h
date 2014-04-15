#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ParticleModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setParticleModel (ParticleModel* model);
    ~MainWindow();

private slots:
    void on_lineEdit_name_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    ParticleModel* model;
};

#endif // MAINWINDOW_H
