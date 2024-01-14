/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *line_6;
    QLabel *label;
    QLabel *label_3;
    QFrame *line;
    QFrame *line_4;
    QFrame *line_3;
    QFrame *line_7;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *ocrScan;
    QPushButton *ocrResult;
    QPushButton *ml;
    QPushButton *stop;
    QFrame *line_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QPushButton *forward;
    QPushButton *turnLeft;
    QPushButton *remote;
    QPushButton *turnRight;
    QPushButton *backward;
    QPushButton *selfDriving;
    QWidget *layoutWidget2;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLabel *value;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *thresholdMinus;
    QPushButton *thresholdPlus;
    QGridLayout *gridLayout_2;
    QPushButton *leftAngleTurn;
    QPushButton *rightAngleTurn;
    QPushButton *RightAboutTurn;
    QPushButton *LeftAboutTurn;
    QGridLayout *gridLayout_3;
    QPushButton *capture;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cannyMinus;
    QPushButton *cannyPlus;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout;
    QPushButton *qrCode;
    QPushButton *quant;
    QPushButton *area;
    QPushButton *camera;
    QLabel *label_4;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(724, 408);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        line_6 = new QFrame(centralWidget);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(9, 0, 701, 16));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 20, 298, 22));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(280, 50, 171, 22));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(30, 91, 661, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(9, 100, 701, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 300, 701, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(centralWidget);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(10, 350, 701, 20));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(620, 120, 93, 104));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        ocrScan = new QPushButton(layoutWidget);
        ocrScan->setObjectName(QStringLiteral("ocrScan"));
        ocrScan->setCheckable(true);

        verticalLayout_3->addWidget(ocrScan);

        ocrResult = new QPushButton(layoutWidget);
        ocrResult->setObjectName(QStringLiteral("ocrResult"));
        ocrResult->setCheckable(true);
        ocrResult->setAutoRepeat(false);

        verticalLayout_3->addWidget(ocrResult);

        ml = new QPushButton(layoutWidget);
        ml->setObjectName(QStringLiteral("ml"));
        ml->setCheckable(true);

        verticalLayout_3->addWidget(ml);

        stop = new QPushButton(centralWidget);
        stop->setObjectName(QStringLiteral("stop"));
        stop->setGeometry(QRect(450, 270, 91, 30));
        stop->setAutoRepeat(true);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(30, 10, 661, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(130, 110, 257, 140));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        forward = new QPushButton(layoutWidget1);
        forward->setObjectName(QStringLiteral("forward"));
        forward->setAutoRepeat(true);

        gridLayout->addWidget(forward, 0, 1, 1, 1);

        turnLeft = new QPushButton(layoutWidget1);
        turnLeft->setObjectName(QStringLiteral("turnLeft"));
        turnLeft->setAutoRepeat(true);

        gridLayout->addWidget(turnLeft, 1, 0, 1, 1);

        remote = new QPushButton(layoutWidget1);
        remote->setObjectName(QStringLiteral("remote"));
        remote->setCheckable(true);
        remote->setChecked(false);

        gridLayout->addWidget(remote, 1, 1, 1, 1);

        turnRight = new QPushButton(layoutWidget1);
        turnRight->setObjectName(QStringLiteral("turnRight"));
        turnRight->setAutoRepeat(true);

        gridLayout->addWidget(turnRight, 1, 2, 1, 1);

        backward = new QPushButton(layoutWidget1);
        backward->setObjectName(QStringLiteral("backward"));
        backward->setAutoRepeat(true);

        gridLayout->addWidget(backward, 2, 1, 1, 1);

        selfDriving = new QPushButton(layoutWidget1);
        selfDriving->setObjectName(QStringLiteral("selfDriving"));
        selfDriving->setCheckable(true);
        selfDriving->setAutoRepeat(false);

        gridLayout->addWidget(selfDriving, 3, 1, 1, 1);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(250, 320, 361, 33));
        formLayout = new QFormLayout(layoutWidget2);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        value = new QLabel(layoutWidget2);
        value->setObjectName(QStringLiteral("value"));

        formLayout->setWidget(0, QFormLayout::FieldRole, value);

        layoutWidget3 = new QWidget(centralWidget);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(400, 110, 211, 155));
        verticalLayout_2 = new QVBoxLayout(layoutWidget3);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        thresholdMinus = new QPushButton(layoutWidget3);
        thresholdMinus->setObjectName(QStringLiteral("thresholdMinus"));
        thresholdMinus->setAutoRepeat(true);

        horizontalLayout->addWidget(thresholdMinus);

        thresholdPlus = new QPushButton(layoutWidget3);
        thresholdPlus->setObjectName(QStringLiteral("thresholdPlus"));
        thresholdPlus->setAutoRepeat(true);

        horizontalLayout->addWidget(thresholdPlus);


        verticalLayout_2->addLayout(horizontalLayout);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        leftAngleTurn = new QPushButton(layoutWidget3);
        leftAngleTurn->setObjectName(QStringLiteral("leftAngleTurn"));
        leftAngleTurn->setAutoRepeat(true);

        gridLayout_2->addWidget(leftAngleTurn, 0, 0, 1, 1);

        rightAngleTurn = new QPushButton(layoutWidget3);
        rightAngleTurn->setObjectName(QStringLiteral("rightAngleTurn"));
        rightAngleTurn->setAutoRepeat(true);

        gridLayout_2->addWidget(rightAngleTurn, 0, 1, 1, 1);

        RightAboutTurn = new QPushButton(layoutWidget3);
        RightAboutTurn->setObjectName(QStringLiteral("RightAboutTurn"));
        RightAboutTurn->setAutoRepeat(true);

        gridLayout_2->addWidget(RightAboutTurn, 1, 1, 1, 1);

        LeftAboutTurn = new QPushButton(layoutWidget3);
        LeftAboutTurn->setObjectName(QStringLiteral("LeftAboutTurn"));
        LeftAboutTurn->setAutoRepeat(true);

        gridLayout_2->addWidget(LeftAboutTurn, 1, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        capture = new QPushButton(layoutWidget3);
        capture->setObjectName(QStringLiteral("capture"));
        capture->setAutoRepeat(true);

        gridLayout_3->addWidget(capture, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);

        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(180, 270, 172, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        cannyMinus = new QPushButton(layoutWidget_2);
        cannyMinus->setObjectName(QStringLiteral("cannyMinus"));
        cannyMinus->setAutoRepeat(true);

        horizontalLayout_2->addWidget(cannyMinus);

        cannyPlus = new QPushButton(layoutWidget_2);
        cannyPlus->setObjectName(QStringLiteral("cannyPlus"));
        cannyPlus->setAutoRepeat(true);

        horizontalLayout_2->addWidget(cannyPlus);

        layoutWidget4 = new QWidget(centralWidget);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 121, 109, 140));
        verticalLayout = new QVBoxLayout(layoutWidget4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        qrCode = new QPushButton(layoutWidget4);
        qrCode->setObjectName(QStringLiteral("qrCode"));
        qrCode->setCheckable(true);

        verticalLayout->addWidget(qrCode);

        quant = new QPushButton(layoutWidget4);
        quant->setObjectName(QStringLiteral("quant"));
        quant->setCheckable(true);

        verticalLayout->addWidget(quant);

        area = new QPushButton(layoutWidget4);
        area->setObjectName(QStringLiteral("area"));
        area->setCheckable(true);

        verticalLayout->addWidget(area);

        camera = new QPushButton(layoutWidget4);
        camera->setObjectName(QStringLiteral("camera"));
        camera->setCheckable(true);

        verticalLayout->addWidget(camera);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(240, 70, 269, 22));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "                 rsBOT CONTROL", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "by: JOSHUA AYANLADE", nullptr));
        ocrScan->setText(QApplication::translate("MainWindow", "OCR Scan", nullptr));
        ocrResult->setText(QApplication::translate("MainWindow", "OCR Result", nullptr));
        ml->setText(QApplication::translate("MainWindow", "Machine L", nullptr));
        stop->setText(QApplication::translate("MainWindow", "STOP", nullptr));
        forward->setText(QApplication::translate("MainWindow", "Forward", nullptr));
        turnLeft->setText(QApplication::translate("MainWindow", "Turn Left", nullptr));
        remote->setText(QApplication::translate("MainWindow", "Cam/Rmt", nullptr));
        turnRight->setText(QApplication::translate("MainWindow", "Turn Right", nullptr));
        backward->setText(QApplication::translate("MainWindow", "Backward", nullptr));
        selfDriving->setText(QApplication::translate("MainWindow", "Self Drive", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Status:", nullptr));
        value->setText(QString());
        thresholdMinus->setText(QApplication::translate("MainWindow", "Threshold-", nullptr));
        thresholdPlus->setText(QApplication::translate("MainWindow", "Threshold+", nullptr));
        leftAngleTurn->setText(QApplication::translate("MainWindow", "Left ang Trn", nullptr));
        rightAngleTurn->setText(QApplication::translate("MainWindow", "Rght ang Turn", nullptr));
        RightAboutTurn->setText(QApplication::translate("MainWindow", "Rotate Right", nullptr));
        LeftAboutTurn->setText(QApplication::translate("MainWindow", "Rotate Left", nullptr));
        capture->setText(QApplication::translate("MainWindow", "Capture", nullptr));
        cannyMinus->setText(QApplication::translate("MainWindow", "Canny", nullptr));
        cannyPlus->setText(QApplication::translate("MainWindow", "Sd Engage", nullptr));
        qrCode->setText(QApplication::translate("MainWindow", "QR/Bar Scan", nullptr));
        quant->setText(QApplication::translate("MainWindow", "quantity", nullptr));
        area->setText(QApplication::translate("MainWindow", "Area Estimate", nullptr));
        camera->setText(QApplication::translate("MainWindow", "Camera", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "                       05-2023", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
