#ifndef ROBOT_H
#define ROBOT_H

#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include <iostream>
#include <wiringPi.h>
#include <string>
#include <chrono>
#include <zbar.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>

class Robot{
public:
		Robot();
		//~Robot();
		
		//Objects
		raspicam::RaspiCam_Cv webcam;
		std::stringstream ss;
		std::stringstream ssL, ssR;
		int Data();
		tesseract::TessBaseAPI tess;
	
		//boolean variable for features
		bool ocrMode;
		bool ocrResult;
		bool quantityMode;
		bool areaMode;
		bool mlMode;
		bool selfDriveMode;
		bool qrMode;
		bool camMode;
		
		//HardwarePins variables
		int Spin1,Spin2,Spin3,Spin4,CamPin;
		int Gpin1,Gpin2,Gpin3,Gpin4;
		int IRpin1,IRpin2,IRpin3,IRpin4;
		
		//function declaration
		void cameraSetup(int argc, char **argv,raspicam::RaspiCam_Cv &webcam);
		std::string getTime();
		void selfDrive();
		void areaPerspective();
		void imgProc();
		void control(int x,int y);
		void areaEstimate(int a);
		void getContour();
		void quantGetContour();
		void scanBarcodes(cv::Mat& frame);
		void saveText();
		void ocr();
		void kDetect();
		void mL();
		bool initCamera();
		void initTesseract();
		
		
		
		void selfDriveControl();
		void areaEstimateControl();
		void quantEstimateControl();
		void qrModeControl();
		void ocrModeControl();
		void ocrResultControl();
		void camModeControl();
		void objectDectectControl();
		void wiringPiSetup_Slave(int Spn1,int Spn2, int Spn3, int Spn4, int CamPn);
		void wiringPiSetup_IrRemote(int IRpn1,int IRpn2, int IRpn3);
		void wiringPiSetup_GUI(int Gpn1,int Gpn2, int Gpn3, int Gpn4);	

private:
		
		//Area Estimation variables
		std::stringstream area_ss;
		cv::Mat imgPers, imgGray,imgBlur,imgCanny, imgDil;
		int cMin,cMax;
		int xMin,xMax,yMin,yMax;
		
		//Self Drive Variables
		cv::Mat frame,persFrame,grayFrame,thresholdFrame,edgeFrame,finalFrame,finalFrameCopy;
		std::vector<int>laneArray, rTurnArray, lTurnArray;
		int deviation;
		int sumStripL,sumStripR;
		
		int tMin=55;  //55,117,172
		int d,t,data;
		
		//Quantity variables
		std::stringstream count_ss;

		//QR/Bar Code variables
		// The name of the text file to save the results
		const std::string OUTPUT_FILE ="/home/pi/Desktop/barcodes.txt";
		
		typedef struct{
			std::string type;
			std::string data;
			std::vector <cv::Point> location;
			
		}object;
		
		//OCR variables
		const char* word;
		cv::Mat ocrFrame;

		const std::string OCR_FILE ="/home/pi/Desktop/rsBOT/rsBOT exe/ocr/ocr.txt";

		//ML variables
		cv::CascadeClassifier kModel;
		cv::Mat kFrame;
		std::vector<cv::Rect> k;
		cv::Mat k_roi,k_gray;
		int dist;

		//function declaration
		
		void capture();
		void ocrCapture();
		void perspective();
		void camera();
		void threshold();
		void strip();
		void laneDetect();
		void turn();

};


#endif
