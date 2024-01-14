#include "Robot.h"


using namespace cv;
using namespace raspicam;
using namespace std;
using namespace zbar;

//Constructor
Robot::Robot(){
}

/*
Robot::~Robot(){
}
*/ 

void Robot::cameraSetup(int argc, char **argv, raspicam::RaspiCam_Cv &webcam){
	webcam.set ( CAP_PROP_FRAME_WIDTH,  ( "-w",argc,argv,640 ) );  //400
    webcam.set ( CAP_PROP_FRAME_HEIGHT,  ( "-h",argc,argv,480 ) );  //240
    //webcam.set ( CAP_PROP_BRIGHTNESS, ( "-br",argc,argv,70 ) );
    //webcam.set ( CAP_PROP_CONTRAST ,( "-co",argc,argv,70 ) ); //60
    //webcam.set ( CAP_PROP_SATURATION,  ( "-sa",argc,argv,50 ) );
    //webcam.set ( CAP_PROP_GAIN,  ( "-g",argc,argv ,100 ) ); //50
    webcam.set ( CAP_PROP_FPS,  ( "-fps",argc,argv,100));

}

bool Robot::initCamera(){
	if(!webcam.open()){
		cout<<"Not connected!"<<endl;
		return -1;
	}
    return true;
}

void Robot::initTesseract(){
	// Initialize Tesseract OCR engine
	tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
	//tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);  //PSM_SINGLE_BLOCK  PSM_SPARSE_TEXT
	tess.SetPageSegMode(tesseract::PSM_SPARSE_TEXT);
}
string Robot::getTime(){
	time_t ct = std::time(0);
	char* currentTD = ctime(&ct);
	
	return currentTD;
}


void Robot::capture(){
	//webcam>> frame;
	webcam.grab();
	webcam.retrieve(frame);
	//cv::cvtColor(frame,frame,cv::COLOR_BRG2RGB);
	cv::cvtColor(frame,kFrame,cv::COLOR_BGR2RGB);
	
	//setup window for displaying video feed
	namedWindow("frame",WINDOW_KEEPRATIO);
	resizeWindow("frame",640,480);
	moveWindow("frame",0,100);
	imshow("frame",frame);
}

void Robot::ocrCapture(){
	//webcam>> ocrFrame;
	webcam.grab();
	webcam.retrieve(ocrFrame);
	
	//create window to display camera feed
	namedWindow("Camera Feed",WINDOW_AUTOSIZE);
}

void Robot::perspective(){
	Point2f srcPoint[]= {Point2f(169,120),Point2f(209,120),Point2f(207,240),Point2f(167,240)};
	Point2f dstPoint[] = {Point2f(174,0),Point2f(204,0),Point2f(202,240),Point2f(172,240)};
	
	Mat matrix = getPerspectiveTransform(srcPoint,dstPoint);
	warpPerspective(frame,persFrame,matrix,Size(640,480));
}

int Robot::Data(){
	int a,b,c,d;
	
	a = digitalRead(Gpin1);
	b = digitalRead(Gpin2);
	c = digitalRead(Gpin3);
	d = digitalRead(Gpin4);
	
	data = 8*d + 4*c + 2*b +1*a;
	cout<<"data ID: "<<data<<endl;
	return data;
	
}

void Robot::camera(){
	Robot::capture();
	Robot::getTime();
	int data = Robot::Data();
	
	//to get current time & date
	string ctd = Robot::getTime();
	
	if (data == 10){
		imwrite("/home/pi/Desktop/rsBOT/rsBOT exe/captured_images/imag"+ctd+".jpg",frame);
		digitalWrite(CamPin,1);  //cam feedback
		delay(1000);
	}
	
}

void Robot::threshold(){
	int data = Robot::Data();
	if(data == 9)
	{
		tMin = tMin -1;
		
		if(tMin <0)
		{
			tMin = 0;
		}
	}
	
	else if (data ==8)
	{
		tMin = tMin +1;
		if(tMin >255)
		{
			tMin = 255;
		}
	}
	
	cout<<tMin<<endl;
	
	cvtColor(persFrame,grayFrame,COLOR_RGB2GRAY);
	inRange(grayFrame,tMin,255,finalFrame); //77,92[64] [61]
	//Canny(grayFrame,edgeFrame,41,236,3,false);  //131,293
	//add(thresholdFrame,edgeFrame,finalFrame);
	cvtColor(finalFrame,finalFrame,COLOR_GRAY2RGB);
	cvtColor(finalFrame,finalFrameCopy,COLOR_RGB2BGR);
	
}

void Robot::strip(){
	laneArray.resize(360);
	laneArray.clear();
	for(int i = 0; i < 360; i++)
	{
		Mat roi = finalFrameCopy(Rect(i,140,1,80));  //122,94
		
		//normalize
		divide(255,roi,roi);
		laneArray.push_back((int)(sum(roi)[0]));
	}
}

void Robot::laneDetect(){
	vector<int>::iterator ptr;
	ptr = max_element(laneArray.begin()+5,laneArray.end()-5); //130,230;50
	int dst = distance(laneArray.begin(),ptr);
	
	line(finalFrame,Point2f(dst,0),Point2f(dst,240),Scalar(0,255,0),2);
	
	//int frameCentre = 200;
	int frameCentre = 175;
	line(finalFrame,Point2f(frameCentre,0),Point2f(frameCentre,240),Scalar(0,0,255),2);
	
	deviation = dst - frameCentre;
}

void Robot::turn(){
	rTurnArray.clear();
	rTurnArray.resize(125);
	
	//for rightTurn
	
	for(int j =164; j<=288; j++)
	{
		Mat roiR = finalFrameCopy(Rect(j,120,1,61));  //134
		
		//to normalize pixel value;
		divide(255,roiR,roiR);
		rTurnArray.push_back((int)(sum(roiR)[0]));
	}
	
	sumStripR = sum(rTurnArray)[0];
	
	
	//for leftTurn
	lTurnArray.clear();
	lTurnArray.resize(123);
	
	for (int k =72; k <=194;k++)
	{
		Mat roiL = finalFrameCopy(Rect(k,120,1,61));  
		
		divide(255,roiL,roiL);
		lTurnArray.push_back((int)(sum(roiL)[0]));
	}
	
	sumStripL = sum(lTurnArray)[0];
	
	
	//printValues
	ssR.clear();
	ssR.str(" ");
	ssR<<"rTurn: "<<sumStripR;
	putText(persFrame,ssR.str(),Point2f(1,15),FONT_HERSHEY_PLAIN,1,Scalar(0,0,225),1);
	
	ssL.clear();
	ssL.str(" ");
	ssL<<"lTurn: "<<sumStripL;
	putText(persFrame,ssL.str(),Point2f(1,50),FONT_HERSHEY_PLAIN,1,Scalar(0,0,225),1);
	
	line(persFrame,Point2f(72,120),Point2f(288,120),Scalar(0,255,0),2);
	line(persFrame,Point2f(288,120),Point2f(288,181),Scalar(0,255,0),2);
	line(persFrame,Point2f(72,181),Point2f(288,181),Scalar(0,255,0),2);
	line(persFrame,Point2f(72,120),Point2f(72,181),Scalar(0,255,0),2);
}

void Robot::selfDrive(){
	Robot::getTime();
	Robot::capture();
	Robot::perspective();
	Robot::threshold();
	Robot::strip();
	Robot::laneDetect();
	Robot::turn();
	int data = Robot::Data();
	
	ss.clear();
	ss.str(" ");
	ss<<"deviation: "<<deviation;
	putText(finalFrame,ss.str(),Point2f(1,50),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,0,225),1);
	
	//cout<<"decimal: "<<data<<endl;
	
	//to get current time & date
	string ctd = getTime();
	
	if(data==10){
		imwrite("/home/pi/Desktop/rsBOT/rsBOT exe/captured_images/imag"+ctd+".jpg",frame);
		digitalWrite(CamPin,1);  //cam feedback
		delay(1000);
	
		
	}

	//cout<<"Deviation"<<deviation<<endl;
	
	if(deviation==0)
	{
		digitalWrite(Spin1,0);  //LSB
		digitalWrite(Spin2,0);
		digitalWrite(Spin3,0);
		digitalWrite(Spin4,0);  //MSB
		
		ss.clear();
		ss.str(" ");
		ss<<"Move Forward";
		putText(finalFrame,ss.str(),Point2f(1,20),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,0,225),1);
	}
	
	else if(deviation>0 && deviation<=10)
	{
		digitalWrite(Spin1,1);
		digitalWrite(Spin2,0);
		digitalWrite(Spin3,0);
		digitalWrite(1,0);
		
		ss.clear();
		ss.str(" ");
		ss<<"Turn Right";
		putText(finalFrame,ss.str(),Point2f(1,20),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,0,225),1);
	}
	
	else if(deviation>10 && deviation<=20)
	{
		digitalWrite(Spin1,0);
		digitalWrite(Spin2,1);
		digitalWrite(Spin3,0);
		digitalWrite(1,0);
		
		ss.clear();
		ss.str(" ");
		ss<<"Turn Right";
		putText(finalFrame,ss.str(),Point2f(1,20),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,0,225),1);
	}
	
	else if(deviation>20 and deviation <=100)
	{
		digitalWrite(Spin1,1);
		digitalWrite(Spin2,1);
		digitalWrite(Spin3,0);
		digitalWrite(Spin4,0);
		
		ss.clear();
		ss.str(" ");
		ss<<"Turn Right";
		putText(finalFrame,ss.str(),Point2f(1,20),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,0,225),1);
	}
	
	else if(deviation<0 && deviation>=-10)
	{
		digitalWrite(Spin1,0);
		digitalWrite(Spin2,0);
		digitalWrite(Spin3,1);
		digitalWrite(Spin4,0);
		
		ss.clear();
		ss.str(" ");
		ss<<"Turn Left";
		putText(finalFrame,ss.str(),Point2f(1,20),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,0,225),1);
	}
	
	else if(deviation<-10 && deviation>=-20)
	{
		digitalWrite(Spin1,1);
		digitalWrite(Spin2,0);
		digitalWrite(Spin3,1);
		digitalWrite(Spin4,0);
		
		ss.clear();
		ss.str(" ");
		ss<<"Turn Left";
		putText(finalFrame,ss.str(),Point2f(1,20),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,0,225),1);
	}
	
	else if(deviation<-20 and deviation >=-100)
	{
		digitalWrite(Spin1,0);
		digitalWrite(Spin2,1);
		digitalWrite(Spin3,1);
		digitalWrite(Spin4,0);
		
		ss.clear();
		ss.str(" ");
		ss<<"Turn Left";
		putText(finalFrame,ss.str(),Point2f(1,20),FONT_HERSHEY_DUPLEX,0.75,Scalar(0,0,225),1);
	}
	
	
	if(deviation >100 and deviation <120 )  //dec 9
	{ 
		digitalWrite(Spin1,1);
		digitalWrite(Spin2,0);
		digitalWrite(Spin3,0);
		digitalWrite(Spin4,1);
		//delay(200); //200,300
		
		
	}
	
	if(deviation <-100 and deviation >-120 )  //dec 12
	{ 
		digitalWrite(Spin1,0);
		digitalWrite(Spin2,0);
		digitalWrite(Spin3,1);
		digitalWrite(Spin4,1);
		
		
	}
		
		
}

void Robot::areaPerspective(){
	Point2f srcPoint[]= {Point2f(78,59),Point2f(336,49),Point2f(397,195),Point2f(4,200)};
	Point2f dstPoint[] = {Point2f(0,0),Point2f(360,0),Point2f(360,240),Point2f(0,240)};
	
	Mat matrix = getPerspectiveTransform(srcPoint,dstPoint);
	warpPerspective(frame,imgPers,matrix,Size(360,240));
	
	
	namedWindow("areaPerspective",WINDOW_KEEPRATIO);
	resizeWindow("areaPerspective",640,320);
	imshow("areaPerspective",imgPers);
}

void Robot::imgProc(){
	cMin = 56, cMax = 184;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5,5));
	
	cvtColor(imgPers,imgGray,COLOR_BGR2GRAY);
	GaussianBlur(imgGray,imgBlur,Size(5,5),3,0);
	Canny(imgBlur,imgCanny,cMin,cMax);
	dilate(imgCanny,imgDil,kernel);
	
	namedWindow("dilated",WINDOW_KEEPRATIO);
	resizeWindow("dilated",640,320);
	imshow("dilated",imgDil);
}

void Robot::control(int x, int y){
	if (x<0){
		cout<<"Rotate X clockwise"<<endl;  //dec 14
		digitalWrite(Spin1,0);
		digitalWrite(Spin2,1);
		digitalWrite(Spin3,1);
		digitalWrite(Spin4,1);
	}
	
	else if (x >0){
		cout<<"Rotate X CounterClockwise"<<endl; //dec 13
		digitalWrite(Spin1,1);
		digitalWrite(Spin2,0);
		digitalWrite(Spin3,1);
		digitalWrite(Spin4,1);
	}

	
	else if (y<0){
		cout<<"Rotate Y upward"<<endl;  //dec 10
		digitalWrite(Spin1,0);
		digitalWrite(Spin2,1);
		digitalWrite(Spin3,0);
		digitalWrite(Spin4,1);
	}
	
	else if (y >0){
		cout<<"Rotate Y downward"<<endl;  //dec 12
		digitalWrite(Spin1,0);
		digitalWrite(Spin2,0);
		digitalWrite(Spin3,1);
		digitalWrite(Spin4,1);
	}
}

void Robot::areaEstimate(int a){
	float w = 23;  //reference width in cm
	float h = 17.3; //refrence width in cm
	float refPixelArea = imgPers.size().height * imgPers.size().width;  //in Sq_Pixel
	float refArea = w * h;
	float area = (refArea/refPixelArea)*a;
	
	//cout<<"Area Estimate: "<<area<<" cm2"<<endl;
	area_ss.clear();
	area_ss.str(" ");
	area_ss<<"Area Estimate: "<<area<<" cm2";
	putText(frame,area_ss.str(),Point2f(1,30),FONT_HERSHEY_PLAIN,2,Scalar(0,0,225),2);
}

void Robot::getContour(){
	Robot::capture();
	Robot::areaPerspective();
	Robot::imgProc();
	
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	int area, count=0;
	
	findContours(imgDil, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //contours.size returns number of detected object
	//cout<<contours.size()<<endl;
	
	vector<vector<Point>> conPoly(contours.size());   //this is 2d array with size = contours.size; conPoly[size]
	vector<Rect> boundRect(contours.size());
	Point myPoint(0,0);
	int xDev, yDev;
	int xCenter = 360/2, yCenter = 240/2;
	
	//to filter noise
	for(int i=0; i<contours.size(); i++){
		area = contourArea(contours[i]);
		//cout<<area<<endl;
		if(area>1600){
			count+=1;
			//cout<<area<<endl;

			float peri = arcLength(contours[i],true);
			approxPolyDP(contours[i], conPoly[i], 0.02*peri,true);     //conPoly[i].size returns the number of edges detected for each object
			drawContours(imgPers,conPoly,i,Scalar(255,0,255),2);
			
			boundRect[i] = boundingRect(conPoly[i]);
			rectangle(imgPers,boundRect[i].tl(),boundRect[i].br(), Scalar(0,255,0),2);
			
			
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y + boundRect[i].width / 2;
			line(imgPers,Point(myPoint.x,0),Point(myPoint.x,240), Scalar(0,255,0),2);
			line(imgPers,Point(0,myPoint.y),Point(360,myPoint.y), Scalar(0,255,0),2);
			
			xDev = xCenter - myPoint.x;
			yDev = yCenter - myPoint.y;
			
			areaEstimate(area);
		}
		
	}
	
	namedWindow("perspect",WINDOW_KEEPRATIO);
	resizeWindow("perspect",640,480);
	imshow("perspect",imgPers);
}

void Robot::quantGetContour(){
	Robot::capture();
	Robot::areaPerspective();
	Robot::imgProc();
	
	vector<vector<Point>> contours;
	vector<Vec4i> hierachy;
	int area, count=0;
	
	findContours(imgDil, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //contours.size returns number of detected object
	//cout<<contours.size()<<endl;
	
	vector<vector<Point>> conPoly(contours.size());   //this is 2d array with size = contours.size; conPoly[size]
	vector<Rect> boundRect(contours.size());
	Point myPoint(0,0);
	int xDev, yDev;
	int xCenter = 360/2, yCenter = 240/2;
	
	//to filter noise
	for(int i=0; i<contours.size(); i++){
		area = contourArea(contours[i]);
		//cout<<area<<endl;
		
		if(area>1600){
			count+=1;
			//cout<<area<<endl;

			float peri = arcLength(contours[i],true);
			approxPolyDP(contours[i], conPoly[i], 0.02*peri,true);     //conPoly[i].size returns the number of edges detected for each object
			drawContours(imgPers,conPoly,i,Scalar(255,0,255),2);
			
			boundRect[i] = boundingRect(conPoly[i]);
			rectangle(imgPers,boundRect[i].tl(),boundRect[i].br(), Scalar(0,255,0),2);
			
			
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;
			myPoint.y = boundRect[i].y + boundRect[i].width / 2;
			line(imgPers,Point(myPoint.x,0),Point(myPoint.x,240), Scalar(0,255,0),2);
			line(imgPers,Point(0,myPoint.y),Point(360,myPoint.y), Scalar(0,255,0),2);
			
			xDev = xCenter - myPoint.x;
			yDev = yCenter - myPoint.y;
			
			Robot::areaEstimate(area);
		}
		
	}
	//cout<<count<<endl;
	
	count_ss.clear();
	count_ss.str(" ");
	count_ss<<"Quantity: "<<count;
	putText(frame,count_ss.str(),Point2f(1,30),FONT_HERSHEY_PLAIN,2,Scalar(0,0,225),2);
}

void Robot::scanBarcodes(cv::Mat& frame){
	Robot::Data();
	Robot::getTime();
	string ctd = Robot::getTime();
	
	//Create a zbar scanner
	zbar::ImageScanner scanner;

	// Configure the scanner to look for QR and barcodes
	scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
	scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);

	// Convert the frame to grayscale
	cv::Mat gray;
	cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

	// Wrap the frame data in a zbar image
	zbar::Image image(gray.cols, gray.rows, "Y800", gray.data, gray.cols * gray.rows);

	// Scan the image for barcodes
	int num = scanner.scan(image);

	// Open the output file for writing
	//std::ofstream out(OUTPUT_FILE);
	std::ofstream out(OUTPUT_FILE, std::ios::app);

	// Draw bounding boxes around the barcodes and display the results
	for (zbar::Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {
	// Get the bounding box coordinates
	int x = symbol->get_location_x(0);
	int y = symbol->get_location_y(0);
	int w = symbol->get_location_x(2) - x;
	int h = symbol->get_location_y(2) - y;

	// Draw a bounding box around the barcode
	cv::rectangle(frame, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 0), 2);


	// Save the barcode type and data to the output file
	if(data==10){
	out << ctd + symbol->get_type_name() << ": " << symbol->get_data() + "\n" << std::endl;
	digitalWrite(CamPin,1);
	delay(1000);
	}



	// Display the barcode type and data
	std::stringstream text;
	text << symbol->get_type_name() << ": " << symbol->get_data();
	//cv::putText(frame, text.str(), cv::Point(x, y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
	cv::putText(frame, text.str(), cv::Point(x, y - 10), cv::FONT_HERSHEY_DUPLEX, 3, cv::Scalar(0, 255, 0), 2);
	}

	// Close the output file
	out.close();
}

void Robot::saveText(){
	fstream myFile;
    
	myFile.open("//home//pi//Desktop//rsBOT//rsBOT exe//ocr//ocr.txt", fstream::app);
	if(myFile.is_open()){
		myFile<<word<<endl;
            cout<<"Successfully Saved"<<endl;
	}
    cout<<word<<endl;
	 //delete [] outText;
}

void Robot::ocr(){
	char* outt;
	
	Robot::capture();
	
	//open the output file for writing
	std::ofstream txt(OCR_FILE, std::ios::app);
	
	//Extract text from frame
	tess.SetImage((uchar*)frame.data, frame.size().width, frame.size().height, frame.channels(), frame.step1());
    tess.Recognize(0);
    tesseract::ResultIterator* ri = tess.GetIterator();
    tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
    while (ri->Next(level)) {
            // Get bounding box for word
            int left, top, right, bottom;
            ri->BoundingBox(level, &left, &top, &right, &bottom);

            // Get OCR text for word
            string word = ri->GetUTF8Text(level);

            // Get confidence level for OCR result
            double confidence = ri->Confidence(level);

            // If confidence level is above threshold, draw bounding box and display OCR text on camera feed
            if (confidence > 90) {
                // Draw bounding box
                rectangle(frame, Point(left, top), Point(right, bottom), Scalar(0, 0, 255), 2);

                // Display OCR text
                putText(frame, word, Point(left, top - 5), FONT_HERSHEY_DUPLEX, 2, Scalar(0, 0, 255), 2);

                // Save OCR result to file
                
                if (data == 10){
			 
					txt << word << "\n" << std::endl;
					digitalWrite(CamPin,1);
					delay(1000);
			 
				}
            }
            
           
        }
        txt.close();

    // Display frame with bounding boxes and recognized text
    cv::imshow("frame", frame);
 
	
}

void Robot::kDetect(){
	Robot::capture();
	
	if(!kModel.load("//home//pi//Desktop//rsBOT//rsBOT exe//ML models//k_model.xml"))
	{
		cout<<"Unable to Open kModel"<<endl;
	}
	
	
	k_roi = kFrame(Rect(320,0,320,480));
	cvtColor(k_roi,k_gray,COLOR_RGB2GRAY);
	equalizeHist(k_gray,k_gray);
	kModel.detectMultiScale(k_gray,k);
	
	for (int i=0; i<k.size(); i++)
	{
		Point p1(k[i].x, k[i].y);
		Point p2(k[i].x + k[i].width, k[i].y + k[i].height);
		
		rectangle(k_roi,p1,p2,Scalar(0,0,255),2);
		putText(k_roi,"zone k",p1, FONT_HERSHEY_DUPLEX,1,Scalar(0,0,255),2);
		
		dist = 249.97 - 0.677*(p2.x-p1.x);
		
		ss.clear();
		ss.str(" ");
		ss<<"Dist: "<<dist<<" cm";
		//ss<<"x_dim:"<<p2.x-p1.x;
		putText(k_roi,ss.str(),Point2f(1,50),FONT_HERSHEY_DUPLEX,0.75, Scalar(0,255,0),2);
	}
	
}

void Robot::mL(){
	Robot::kDetect();
	namedWindow("kFrame",WINDOW_KEEPRATIO);
	moveWindow("kFrame",1280,100);//1280,100
	resizeWindow("kFrame",640,360);//640,480
	imshow("kFrame",k_roi);
}

void Robot::wiringPiSetup_Slave(int Spn1,int Spn2, int Spn3, int Spn4, int CamPn){
	Spin1 = Spn1;
	Spin2 = Spn2;
	Spin3 = Spn3;
	Spin4 = Spn4;
	
	//wiringPiSetup();
	
	pinMode(Spin1,OUTPUT);
	pinMode(Spin2,OUTPUT);
	pinMode(Spin3,OUTPUT);
	pinMode(Spin4,OUTPUT);
	pinMode(CamPin,OUTPUT);
}

void Robot::wiringPiSetup_IrRemote(int IRpn1,int IRpn2, int IRpn3){
	IRpin1 = IRpn1;
	IRpin2 = IRpn2;
	IRpin3 = IRpn3;

	//wiringPiSetup();
	
	pullUpDnControl(IRpin1,0);
	pullUpDnControl(IRpin2,0);
	pullUpDnControl(IRpin3,0);
}

void Robot::wiringPiSetup_GUI(int Gpn1,int Gpn2, int Gpn3, int Gpn4){
	Gpin1 = Gpn1;
	Gpin2 = Gpn2;
	Gpin3 = Gpn3;
	Gpin4 = Gpn4;
	
	//wiringPiSetup();
	
	pullUpDnControl(Gpin1,0);
	pullUpDnControl(Gpin2,0);
	pullUpDnControl(Gpin3,0);
	pullUpDnControl(Gpin4,0);
}

void Robot::selfDriveControl(){
	selfDriveMode = true;
	//webcam.set ( CAP_PROP_FRAME_WIDTH,  ( "-w",argc,argv,400 ) );  //400
	//webcam.set ( CAP_PROP_FRAME_HEIGHT,  ( "-h",argc,argv,240 ) );  //240
	while(selfDriveMode){
		Robot::selfDrive();
		// Display Text on frame window
		namedWindow("finalFrame",WINDOW_KEEPRATIO);
		resizeWindow("finalFrame",640,480);
		moveWindow("finalFrame",1280,100);
		imshow("finalFrame",finalFrame);
		
		int data = Robot::Data();
		if(data == 14){
			selfDriveMode = false;
			destroyAllWindows();
		}
		
		waitKey(1);
	}
}
void Robot::areaEstimateControl(){
	areaMode = true;
	while(areaMode){
		Robot::getContour();
		// Display the quantity on frame window
		cv::imshow("frame", frame);
		int data = Robot::Data();
		if(data == 14){
			areaMode = false;
			destroyAllWindows();
		}
		
		waitKey(1);
		
	}
}
void Robot::quantEstimateControl(){
	quantityMode = true;
	while(quantityMode){
		Robot::quantGetContour();
		// Display the quantity on frame window
		cv::imshow("frame", frame);
		int data = Robot::Data();
		if(data == 14){
			quantityMode = false;
			destroyAllWindows();
		}
		
		waitKey(1);
		
	}
}
void Robot::qrModeControl(){
	qrMode = true;
	while(qrMode){
		Robot::capture();
		Robot::scanBarcodes(frame);
		

		// Display the frame with the bounding boxes and results
		cv::imshow("frame", frame);

		int data = Robot::Data();
		if(data == 14){
			qrMode = false;
			destroyAllWindows();
		}
		
		waitKey(1);
		
	}
}
void Robot::ocrModeControl(){
	ocrMode = true;
	while(ocrMode){
		//capture();
		Robot::ocr();
		int data = Robot::Data();
		
		if(data == 14){
			ocrMode = false;
			destroyAllWindows();						
	}
	waitKey(1);
}
}
void Robot::ocrResultControl(){
	ocrResult = true;
	Robot::ocr();
	while(ocrResult){
		int data = Robot::Data();
		
		if(data == 14){
			ocrResult = false;
			destroyAllWindows();
		}
		
		waitKey(1);
		
	}
}
void Robot::camModeControl(){
	camMode = true;
	while(camMode){
		Robot::camera();
		int data = Robot::Data();
		if(data == 14){
			camMode = false;
			destroyAllWindows();
		}
		
		waitKey(1);
		
	}
}
void Robot::objectDectectControl(){
	mlMode = true;
	while(mlMode){
		Robot::mL();
		int data = Robot::Data();
		if(data == 14){
			mlMode = false;
			destroyAllWindows();
		}
		
		waitKey(1);
		
	}

}

	
