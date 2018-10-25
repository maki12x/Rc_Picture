#include "mavrosCommand.hpp"

using namespace std;
using namespace cv;

int frequency = 20;
int loopCounter = 0;
int cntr = 0;

Mat frame;

int main(int argc, char* argv[]){

	ros::init(argc, argv, "rc_picture");
	mavrosCommand command;
	
	ros::Rate loop_rate(frequency);
	sleep(1);
		
	VideoCapture cap(0);
	
	cap.set(CV_CAP_PROP_FRAME_WIDTH,1920);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,1080);
	
	if (cap.isOpened() == false)  
	{
		cout << "Cannot open the video camera" << endl;
		return -1;
	} 
	
	while (ros::ok()) 
	{
				
		if (loopCounter >= 40 && command.getRCInput() > 1500)
		{
			cap.read(frame);
			thread save = thread(savePicture, frame, cntr);
			save.detach();
			cntr++;
			loopCounter = 0;
		}
		
		loopCounter++;
		ros::spinOnce();
		loop_rate.sleep();
	}	
	cap.release();
	return 0;
}
