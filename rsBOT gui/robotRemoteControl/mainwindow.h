#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <wiringPi.h>
#include <QTimer>
#include<QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //QTimer function declaration
    QTimer *timeCounter = new QTimer(this);
    void timeOutFunction();

    bool pressed;

private slots:


    void on_remote_clicked();

    void on_thresholdPlus_clicked();

    void on_thresholdMinus_clicked();

    void on_forward_clicked();

    void on_turnLeft_clicked();

    void on_turnRight_clicked();

    void on_backward_clicked();

    void on_stop_clicked();

    void on_leftAngleTurn_clicked();

    void on_rightAngleTurn_clicked();

    void on_RightAboutTurn_clicked();

    void on_capture_clicked();


    void on_LeftAboutTurn_clicked();



    void on_qrCode_clicked();

    void on_quant_clicked();

    void on_area_clicked();

    void on_ocrScan_clicked();

    void on_ocrResult_clicked();

    void on_ml_clicked();

    void on_selfDriving_clicked();

    void on_cannyMinus_clicked();

    void on_cannyPlus_clicked();

    void on_camera_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
