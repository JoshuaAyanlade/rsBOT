#include "Robot.h"

using namespace cv;
using namespace raspicam;
using namespace std;
using namespace zbar;

//*****MAIN FUNCTION******
int main(int argc, char **argv)
{
	wiringPiSetup();
	Robot robot;
	robot.cameraSetup(argc, argv,robot.webcam);
	robot.wiringPiSetup_IrRemote(12,13,14); //IrRemote Control Pins
	robot.wiringPiSetup_Slave(21,22,23,1,11); //Slave Controller Pins
	robot.wiringPiSetup_GUI(4,5,6,10);		//GUI Control Pins
	
	if(!robot.initCamera()){
		return -1;
	}
	
	robot.initTesseract();


	

	while(true)
	{
		int data = robot.Data();		
		if(data == 7){
			robot.selfDriveControl();	
		}
		
		if(data == 3){
			robot.areaEstimateControl();
		}
		
		if(data == 2){
			robot.quantEstimateControl();
		}
		
		if(data == 1){
			robot.qrModeControl();
		}
		
		if(data == 4){
			robot.ocrModeControl();
		}
		
		if(data == 5){
			robot.ocrResultControl();
		}
		
		if(data == 13){
			robot.camModeControl();

		}
		
		if(data == 6){
			robot.objectDectectControl();
		}	
	
		
	}
	
	return 0;
}



