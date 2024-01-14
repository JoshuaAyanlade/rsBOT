#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<wiringPi.h>
#include <QTextStream>
#include <QTime>
#include <QDate>


#define OUT1 7
#define OUT2 0
#define OUT3 2
#define OUT4 3
#define OUT5 25
#define IN1 12  // IN pin used has potential of causing problem
#define IN2 13
#define IN3 14


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wiringPiSetup();
    pinMode(OUT1,OUTPUT);
    pinMode(OUT2,OUTPUT);
    pinMode(OUT3,OUTPUT);
    pinMode(OUT4,OUTPUT);
    pinMode(OUT5,OUTPUT);
    pinMode(IN1,INPUT);
    pinMode(IN2,INPUT);
    pinMode(IN3,INPUT);

    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(10,OUTPUT);

    pullUpDnControl(11,0); //camera Feedback

    ui->remote->setChecked(false);

    QObject::connect(timeCounter,&QTimer::timeout,this,QOverload<>::of(&MainWindow::timeOutFunction));
    pressed = false;

    QTextStream out(stdout);

    /*
    QDate cd = QDate::currentDate();
    QTime ct = QTime::currentTime();
    out <<"CurrentDate is: "<<cd.toString()<<endl;
    out <<"CurrentTime is: "<<ct.toString()<<endl;
    */


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeOutFunction(){
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);
}

void MainWindow::on_remote_clicked()
{
    if(ui->remote->isChecked()){
        ui->remote->setText("C Control");
        ui->forward->setText("Upward");
        ui->backward->setText("Dwnward");
        ui->turnLeft->setText("Left");
        ui->turnRight->setText("Right");

        digitalWrite(OUT1,0);  //dec:0; LSB
        digitalWrite(OUT2,0);
        digitalWrite(OUT3,0);
        digitalWrite(OUT4,0);
        digitalWrite(OUT5,0);  //MSB
        ui->value->setText("Camera Nav mode Activated");
    }

    else{
        ui->remote->setText("R Control");
        ui->forward->setText("Forward");
        ui->backward->setText("Backward");
        ui->turnLeft->setText("Turn Left");
        ui->turnRight->setText("Turn Right");

        digitalWrite(OUT1,1);  //dec:1
        digitalWrite(OUT2,0);
        digitalWrite(OUT3,0);
        digitalWrite(OUT4,0);
        digitalWrite(OUT5,0);
        ui->value->setText("Remote Control mode Activated");
    }
}



void MainWindow::on_thresholdPlus_clicked()
{

    ui->thresholdPlus->setAutoRepeat(true);

    digitalWrite(4,0);  //dec:5; LSB
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(10,1);
    delay(100);
    digitalWrite(4,1);  //dec:15; LSB
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(10,1);
    ui->value->setText("Threshold Increased");

}

void MainWindow::on_thresholdMinus_clicked()
{
    ui->thresholdMinus->setAutoRepeat(true);

    digitalWrite(4,1);  //dec:5; LSB
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(10,1);
    delay(100);
    digitalWrite(4,1);  //dec:15; LSB
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(10,1);
    ui->value->setText("Threshold Decreased");
}

void MainWindow::on_forward_clicked()
{
    ui->forward->setAutoRepeat(true);

    digitalWrite(OUT1,0);  //dec:4
    digitalWrite(OUT2,0);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,0);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);
    if(ui->remote->isChecked()){
        ui->value->setText("Moving Camera up..");
    }

    else{
        ui->value->setText("Moving Forward...");
    }
}


void MainWindow::on_turnLeft_clicked()
{
    ui->turnLeft->setAutoRepeat(true);

    digitalWrite(OUT1,1);  //dec:5
    digitalWrite(OUT2,0);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,0);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);

    if(ui->remote->isChecked()){
        ui->value->setText("Turning Camera left..");
    }

    else{
        ui->value->setText("Turning Left...");
    }

}

void MainWindow::on_turnRight_clicked()
{
    ui->turnRight->setAutoRepeat(true);

    digitalWrite(OUT1,0);  //dec:6
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,0);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);

    if(ui->remote->isChecked()){
        ui->value->setText("Turning Camera right..");
    }

    else{
        ui->value->setText("Turning Right...");
    }

}

void MainWindow::on_backward_clicked()
{
    ui->backward->setAutoRepeat(true);

    digitalWrite(OUT1,1);  //dec:7
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,0);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);

    if(ui->remote->isChecked()){
        ui->value->setText("Moving Camera down..");
    }

    else{
        ui->value->setText("Moving Backward...");
    }

}

void MainWindow::on_stop_clicked()
{
    ui->stop->setAutoRepeat(true);

    digitalWrite(OUT1,0);  //dec:8
    digitalWrite(OUT2,0);
    digitalWrite(OUT3,0);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);
    ui->value->setText("stopped");

}

void MainWindow::on_leftAngleTurn_clicked()
{
    ui->leftAngleTurn->setAutoRepeat(true);

    digitalWrite(OUT1,1);  //dec:9
    digitalWrite(OUT2,0);
    digitalWrite(OUT3,0);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);
    ui->value->setText("Making Left Turn...");


}

void MainWindow::on_rightAngleTurn_clicked()
{
    ui->turnLeft->setAutoRepeat(true);

    digitalWrite(OUT1,0);  //dec:10
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,0);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);
    ui->value->setText("Making Right Turn...");

}

void MainWindow::on_RightAboutTurn_clicked()
{
    ui->RightAboutTurn->setAutoRepeat(true);

    digitalWrite(OUT1,1);  //dec:11
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,0);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);
    ui->value->setText("Rotating Rightward...");

}

void MainWindow::on_LeftAboutTurn_clicked()
{
    ui->LeftAboutTurn->setAutoRepeat(true);

    digitalWrite(OUT1,0);  //dec:12
    digitalWrite(OUT2,0);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,0);
    delay(100);
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);
    ui->value->setText("Rotating Leftward...");

}



void MainWindow::on_capture_clicked()
{
    ui->capture->setAutoRepeat(true);

    digitalWrite(4,0);  //dec:10; LSB
    digitalWrite(5,1);
    digitalWrite(6,0);
    digitalWrite(10,1);
    delay(500);  //500
    digitalWrite(4,1);  //dec:15; LSB
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(10,1);

    ui->value->setText("Capturing...");

    //qDebug()<<digitalRead(IN1);

        qDebug()<<digitalRead(11);
    int a,b,c;

        a = digitalRead(IN1);
        b = digitalRead(IN2);
        c = digitalRead(IN3);

        //int d = 4*c + 2*b + a;   //d==4
    if(digitalRead(11)==HIGH){
        QDate cd = QDate::currentDate();
        QTime ct = QTime::currentTime();

        ui->value->setText("Image captured on "+ cd.toString()+" "+ct.toString());
    }
    else{
        ui->value->setText("Image not saved");
    }

}


void MainWindow::on_qrCode_clicked()
{
    if(ui->qrCode->isChecked()){
        ui->qrCode->setText("Stop QR");

        digitalWrite(4,1);  //dec:1; LSB
        digitalWrite(5,0);
        digitalWrite(6,0);
        digitalWrite(10,0);

        digitalWrite(OUT1,1);  //dec:17; LSB
        digitalWrite(OUT2,0);
        digitalWrite(OUT3,0);
        digitalWrite(OUT4,0);
        digitalWrite(OUT5,1);

        ui->value->setText("QR Scanning mode Activated");
    }

    else{
        ui->qrCode->setText("QR/Bar Scan");

        digitalWrite(4,0);  //dec:14; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,1);

        digitalWrite(OUT1,1);
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,1);
        digitalWrite(OUT5,1);

        ui->value->setText("QR Scanning mode Deactivated");
    }
}





void MainWindow::on_quant_clicked()
{
    if(ui->quant->isChecked()){
        ui->quant->setText("Stop");

        digitalWrite(4,0);  //dec:2; LSB
        digitalWrite(5,1);
        digitalWrite(6,0);
        digitalWrite(10,0);

        digitalWrite(OUT1,0);  //dec:16; LSB
        digitalWrite(OUT2,0);
        digitalWrite(OUT3,0);
        digitalWrite(OUT4,0);
        digitalWrite(OUT5,1);

        ui->value->setText("Quantity mode Activated");
    }

    else{
        ui->quant->setText("Quantity");

        digitalWrite(4,0);  //dec:14; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,1);

        digitalWrite(OUT1,1);
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,1);
        digitalWrite(OUT5,1);

        ui->value->setText("Quantity mode Deactivated");
    }

}

void MainWindow::on_area_clicked()
{
    if(ui->area->isChecked()){
        ui->area->setText("Stop");

        digitalWrite(4,1);  //dec:3; LSB
        digitalWrite(5,1);
        digitalWrite(6,0);
        digitalWrite(10,0);

        digitalWrite(OUT1,1);  //dec:15; LSB
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,1);
        digitalWrite(OUT5,0);


        ui->value->setText("Area Estimation mode Activated");
    }

    else{
        ui->area->setText("Area Estimate");

        digitalWrite(4,0);  //dec:14; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,1);

        digitalWrite(OUT1,1);
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,1);
        digitalWrite(OUT5,1);


        ui->value->setText("Area Estimation mode Deactivated");
    }

}

void MainWindow::on_ocrScan_clicked()
{
    if(ui->ocrScan->isChecked()){
        ui->ocrScan->setText("Stop");

        digitalWrite(4,0);  //dec:4; LSB
        digitalWrite(5,0);
        digitalWrite(6,1);
        digitalWrite(10,0);

        digitalWrite(OUT1,0);  //dec:18; LSB
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,0);
        digitalWrite(OUT4,0);
        digitalWrite(OUT5,1);

        ui->value->setText("OCR Scanning mode Activated");
    }

    else{
        ui->ocrScan->setText("OCR Scan");

        digitalWrite(4,0);  //dec:14; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,1);

        digitalWrite(OUT1,1);
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,1);
        digitalWrite(OUT5,1);

        ui->value->setText("OCR Scanning mode Deactivated");
    }
}

void MainWindow::on_ocrResult_clicked()
{
    if(ui->ocrResult->isChecked()){
        ui->ocrResult->setText("Stop");

        digitalWrite(4,1);  //dec:5; LSB
        digitalWrite(5,0);
        digitalWrite(6,1);
        digitalWrite(10,0);

        ui->value->setText("Showing OCR Result...");
    }

    else{
        ui->ocrResult->setText("OCR Result");

        digitalWrite(4,0);  //dec:14; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,1);

        ui->value->setText("OCR Result Closed!");
    }
}

void MainWindow::on_ml_clicked()
{
    if(ui->ml->isChecked()){
        ui->ml->setText("Stop");

        digitalWrite(4,0);  //dec:6; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,0);

        digitalWrite(OUT1,1);  //dec:21; LSB
        digitalWrite(OUT2,0);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,0);
        digitalWrite(OUT5,1);

        ui->value->setText("Machine Learning mode Activated");
    }

    else{
        ui->ml->setText("ML");

        digitalWrite(4,0);  //dec:14; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,1);

        ui->value->setText("Machine Learning mode Deactivated");
    }
}

void MainWindow::on_selfDriving_clicked()    //Control both Rasp & Atmega
{
    if(ui->selfDriving->isChecked()){
        ui->selfDriving->setText("Stop");

        digitalWrite(4,1);  //dec:7; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,0);

        digitalWrite(OUT1,1);  //dec:13; LSB
        digitalWrite(OUT2,0);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,1);
        digitalWrite(OUT5,0);  //MSB

        ui->value->setText("Self Driving mode Activated");
    }

    else{
        ui->selfDriving->setText("Self Drive");

        digitalWrite(4,0);  //dec:14; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,1);

        digitalWrite(OUT1,0);  //dec:14; LSB
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,1);
        digitalWrite(OUT5,0);

        ui->value->setText("Self Driving mode Deactivated");
    }
}

void MainWindow::on_cannyMinus_clicked()
{
    ui->cannyMinus->setAutoRepeat(true);

    digitalWrite(4,1);  //dec:11; LSB
    digitalWrite(5,1);
    digitalWrite(6,0);
    digitalWrite(10,1);
    delay(100);
    digitalWrite(4,1);  //dec:15; LSB
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(10,1);
    ui->value->setText("Canny Decreased");
}

void MainWindow::on_cannyPlus_clicked()
{
    ui->cannyPlus->setAutoRepeat(true);

    digitalWrite(4,0);  //dec:12; LSB
    digitalWrite(5,0);
    digitalWrite(6,1);
    digitalWrite(10,1);
    digitalWrite(OUT1,0);  //dec:20; LSB
    digitalWrite(OUT2,0);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,0);
    digitalWrite(OUT5,1);
    delay(100);
    digitalWrite(4,1);  //dec:15; LSB
    digitalWrite(5,1);
    digitalWrite(6,1);
    digitalWrite(10,1); 
    digitalWrite(OUT1,1);
    digitalWrite(OUT2,1);
    digitalWrite(OUT3,1);
    digitalWrite(OUT4,1);
    digitalWrite(OUT5,1);
    ui->value->setText("Engaged");
}

void MainWindow::on_camera_clicked()
{
    if(ui->camera->isChecked()){
        ui->camera->setText("Stop");

        digitalWrite(4,1);  //dec:13; LSB
        digitalWrite(5,0);
        digitalWrite(6,1);
        digitalWrite(10,1);

        digitalWrite(OUT1,1);  //dec:19; LSB
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,0);
        digitalWrite(OUT4,0);
        digitalWrite(OUT5,1);

        ui->value->setText("Camera mode Activated");
    }

    else{
        ui->camera->setText("Camera");

        digitalWrite(4,0);  //dec:14; LSB
        digitalWrite(5,1);
        digitalWrite(6,1);
        digitalWrite(10,1);

        digitalWrite(OUT1,1);
        digitalWrite(OUT2,1);
        digitalWrite(OUT3,1);
        digitalWrite(OUT4,1);
        digitalWrite(OUT5,1);

        ui->value->setText("Camera mode Deactivated");
    }
}
