/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen_XML;
    QAction *actionSave_XML;
    QAction *actionClose;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QLineEdit *lineEdit_Angle;
    QLabel *label_Angle;
    QLineEdit *lineEdit_Lifetime_Min;
    QLabel *label_Lifetime;
    QComboBox *comboBox_EmitterType;
    QLabel *label_7;
    QLineEdit *lineEdit_name;
    QLabel *label_name;
    QLineEdit *lineEdit_Direction_X;
    QLabel *label_Direction;
    QLabel *label_PPS;
    QLabel *label_Min_Color;
    QLineEdit *lineEdit_Direction_Y;
    QLineEdit *lineEdit_Direction_Z;
    QLineEdit *lineEdit_Lifetime_Max;
    QLineEdit *lineEdit_PPS_Min;
    QLineEdit *lineEdit_PPS_Max;
    QPushButton *pushButton_Color_Min;
    QPushButton *pushButton_Color_Max;
    QLabel *label_MinStartSize;
    QLineEdit *lineEdit_MinStartSize_Y;
    QLineEdit *lineEdit_MinStartSize_X;
    QLabel *label_MaxStartSize;
    QLineEdit *lineEdit_MaxStartSize_X;
    QLineEdit *lineEdit_MaxStartSize_Y;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionOpen_XML = new QAction(MainWindow);
        actionOpen_XML->setObjectName(QStringLiteral("actionOpen_XML"));
        actionSave_XML = new QAction(MainWindow);
        actionSave_XML->setObjectName(QStringLiteral("actionSave_XML"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionClose->setCheckable(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 540, 481));
        lineEdit_Angle = new QLineEdit(centralWidget);
        lineEdit_Angle->setObjectName(QStringLiteral("lineEdit_Angle"));
        lineEdit_Angle->setGeometry(QRect(680, 125, 100, 20));
        label_Angle = new QLabel(centralWidget);
        label_Angle->setObjectName(QStringLiteral("label_Angle"));
        label_Angle->setGeometry(QRect(560, 125, 120, 16));
        label_Angle->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        lineEdit_Lifetime_Min = new QLineEdit(centralWidget);
        lineEdit_Lifetime_Min->setObjectName(QStringLiteral("lineEdit_Lifetime_Min"));
        lineEdit_Lifetime_Min->setGeometry(QRect(680, 150, 47, 20));
        label_Lifetime = new QLabel(centralWidget);
        label_Lifetime->setObjectName(QStringLiteral("label_Lifetime"));
        label_Lifetime->setGeometry(QRect(560, 150, 120, 16));
        label_Lifetime->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        comboBox_EmitterType = new QComboBox(centralWidget);
        comboBox_EmitterType->setObjectName(QStringLiteral("comboBox_EmitterType"));
        comboBox_EmitterType->setGeometry(QRect(680, 60, 100, 22));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(560, 60, 110, 20));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lineEdit_name = new QLineEdit(centralWidget);
        lineEdit_name->setObjectName(QStringLiteral("lineEdit_name"));
        lineEdit_name->setGeometry(QRect(680, 20, 100, 20));
        label_name = new QLabel(centralWidget);
        label_name->setObjectName(QStringLiteral("label_name"));
        label_name->setGeometry(QRect(560, 20, 120, 16));
        label_name->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        lineEdit_Direction_X = new QLineEdit(centralWidget);
        lineEdit_Direction_X->setObjectName(QStringLiteral("lineEdit_Direction_X"));
        lineEdit_Direction_X->setGeometry(QRect(680, 100, 30, 20));
        label_Direction = new QLabel(centralWidget);
        label_Direction->setObjectName(QStringLiteral("label_Direction"));
        label_Direction->setGeometry(QRect(560, 100, 120, 16));
        label_Direction->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        label_PPS = new QLabel(centralWidget);
        label_PPS->setObjectName(QStringLiteral("label_PPS"));
        label_PPS->setGeometry(QRect(560, 175, 120, 16));
        label_PPS->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        label_Min_Color = new QLabel(centralWidget);
        label_Min_Color->setObjectName(QStringLiteral("label_Min_Color"));
        label_Min_Color->setGeometry(QRect(560, 200, 120, 16));
        label_Min_Color->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        lineEdit_Direction_Y = new QLineEdit(centralWidget);
        lineEdit_Direction_Y->setObjectName(QStringLiteral("lineEdit_Direction_Y"));
        lineEdit_Direction_Y->setGeometry(QRect(715, 100, 30, 20));
        lineEdit_Direction_Z = new QLineEdit(centralWidget);
        lineEdit_Direction_Z->setObjectName(QStringLiteral("lineEdit_Direction_Z"));
        lineEdit_Direction_Z->setGeometry(QRect(750, 100, 30, 20));
        lineEdit_Direction_Z->setInputMethodHints(Qt::ImhNone);
        lineEdit_Lifetime_Max = new QLineEdit(centralWidget);
        lineEdit_Lifetime_Max->setObjectName(QStringLiteral("lineEdit_Lifetime_Max"));
        lineEdit_Lifetime_Max->setGeometry(QRect(733, 150, 47, 20));
        lineEdit_PPS_Min = new QLineEdit(centralWidget);
        lineEdit_PPS_Min->setObjectName(QStringLiteral("lineEdit_PPS_Min"));
        lineEdit_PPS_Min->setGeometry(QRect(680, 175, 47, 20));
        lineEdit_PPS_Max = new QLineEdit(centralWidget);
        lineEdit_PPS_Max->setObjectName(QStringLiteral("lineEdit_PPS_Max"));
        lineEdit_PPS_Max->setGeometry(QRect(733, 175, 47, 20));
        pushButton_Color_Min = new QPushButton(centralWidget);
        pushButton_Color_Min->setObjectName(QStringLiteral("pushButton_Color_Min"));
        pushButton_Color_Min->setGeometry(QRect(680, 200, 47, 20));
        pushButton_Color_Min->setAutoFillBackground(false);
        pushButton_Color_Min->setStyleSheet(QLatin1String("background-color: rgb(0, 206, 216);\n"
"border: 0;text-align:left;padding-left:5px;"));
        pushButton_Color_Min->setDefault(false);
        pushButton_Color_Min->setFlat(true);
        pushButton_Color_Max = new QPushButton(centralWidget);
        pushButton_Color_Max->setObjectName(QStringLiteral("pushButton_Color_Max"));
        pushButton_Color_Max->setGeometry(QRect(733, 200, 47, 20));
        pushButton_Color_Max->setFocusPolicy(Qt::StrongFocus);
        pushButton_Color_Max->setAutoFillBackground(false);
        pushButton_Color_Max->setStyleSheet(QLatin1String("background-color: rgb(0, 206, 216);\n"
"border: 0;text-align:left;padding-left:5px;"));
        pushButton_Color_Max->setDefault(false);
        pushButton_Color_Max->setFlat(true);
        label_MinStartSize = new QLabel(centralWidget);
        label_MinStartSize->setObjectName(QStringLiteral("label_MinStartSize"));
        label_MinStartSize->setGeometry(QRect(560, 225, 120, 16));
        label_MinStartSize->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        lineEdit_MinStartSize_Y = new QLineEdit(centralWidget);
        lineEdit_MinStartSize_Y->setObjectName(QStringLiteral("lineEdit_MinStartSize_Y"));
        lineEdit_MinStartSize_Y->setGeometry(QRect(733, 225, 47, 20));
        lineEdit_MinStartSize_X = new QLineEdit(centralWidget);
        lineEdit_MinStartSize_X->setObjectName(QStringLiteral("lineEdit_MinStartSize_X"));
        lineEdit_MinStartSize_X->setGeometry(QRect(680, 225, 47, 20));
        label_MaxStartSize = new QLabel(centralWidget);
        label_MaxStartSize->setObjectName(QStringLiteral("label_MaxStartSize"));
        label_MaxStartSize->setGeometry(QRect(560, 250, 120, 16));
        label_MaxStartSize->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        lineEdit_MaxStartSize_X = new QLineEdit(centralWidget);
        lineEdit_MaxStartSize_X->setObjectName(QStringLiteral("lineEdit_MaxStartSize_X"));
        lineEdit_MaxStartSize_X->setGeometry(QRect(680, 250, 47, 20));
        lineEdit_MaxStartSize_Y = new QLineEdit(centralWidget);
        lineEdit_MaxStartSize_Y->setObjectName(QStringLiteral("lineEdit_MaxStartSize_Y"));
        lineEdit_MaxStartSize_Y->setGeometry(QRect(733, 250, 47, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen_XML);
        menuFile->addAction(actionSave_XML);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        actionOpen_XML->setText(QApplication::translate("MainWindow", "Open particle", 0));
        actionSave_XML->setText(QApplication::translate("MainWindow", "Save to XML", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        lineEdit_Angle->setInputMask(QString());
        lineEdit_Angle->setPlaceholderText(QApplication::translate("MainWindow", "Degrees", 0));
        label_Angle->setText(QApplication::translate("MainWindow", "Angle", 0));
        lineEdit_Lifetime_Min->setInputMask(QString());
        lineEdit_Lifetime_Min->setPlaceholderText(QApplication::translate("MainWindow", "Min", 0));
        label_Lifetime->setText(QApplication::translate("MainWindow", "Life time", 0));
        comboBox_EmitterType->clear();
        comboBox_EmitterType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", 0)
         << QApplication::translate("MainWindow", "Box", 0)
         << QApplication::translate("MainWindow", "Point", 0)
         << QApplication::translate("MainWindow", "Animated Mesh", 0)
         << QApplication::translate("MainWindow", "Cylinder", 0)
         << QApplication::translate("MainWindow", "Mesh", 0)
         << QApplication::translate("MainWindow", "Ring", 0)
         << QApplication::translate("MainWindow", "Sphere", 0)
        );
        label_7->setText(QApplication::translate("MainWindow", "Emitter type", 0));
        label_name->setText(QApplication::translate("MainWindow", "Name", 0));
        lineEdit_Direction_X->setPlaceholderText(QApplication::translate("MainWindow", "X", 0));
        label_Direction->setText(QApplication::translate("MainWindow", "Direction", 0));
        label_PPS->setText(QApplication::translate("MainWindow", "Particles per second", 0));
        label_Min_Color->setText(QApplication::translate("MainWindow", "Start color", 0));
        lineEdit_Direction_Y->setPlaceholderText(QApplication::translate("MainWindow", "Y", 0));
        lineEdit_Direction_Z->setPlaceholderText(QApplication::translate("MainWindow", "Z", 0));
        lineEdit_Lifetime_Max->setPlaceholderText(QApplication::translate("MainWindow", "Max", 0));
        lineEdit_PPS_Min->setInputMask(QString());
        lineEdit_PPS_Min->setPlaceholderText(QApplication::translate("MainWindow", "Min", 0));
        lineEdit_PPS_Max->setPlaceholderText(QApplication::translate("MainWindow", "Max", 0));
        pushButton_Color_Min->setText(QApplication::translate("MainWindow", "Min", 0));
        pushButton_Color_Max->setText(QApplication::translate("MainWindow", "Max", 0));
        label_MinStartSize->setText(QApplication::translate("MainWindow", "Min start size", 0));
        lineEdit_MinStartSize_Y->setPlaceholderText(QApplication::translate("MainWindow", "Y", 0));
        lineEdit_MinStartSize_X->setInputMask(QString());
        lineEdit_MinStartSize_X->setPlaceholderText(QApplication::translate("MainWindow", "X", 0));
        label_MaxStartSize->setText(QApplication::translate("MainWindow", "Max start size", 0));
        lineEdit_MaxStartSize_X->setInputMask(QString());
        lineEdit_MaxStartSize_X->setPlaceholderText(QApplication::translate("MainWindow", "X", 0));
        lineEdit_MaxStartSize_Y->setPlaceholderText(QApplication::translate("MainWindow", "Y", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
