#include <iostream>
#include "mavrosCommand.hpp"

using namespace std;
using namespace ros;
using namespace cv;

string get_username() {
    struct passwd *pwd = getpwuid(getuid());
    if (pwd)
        return pwd->pw_name;
    else
        return "odroid";
}

void savePicture(Mat in_frame, int cntr)
{
	string name = get_username();
	string savingName = "/home/" + name + "/zdj/" + to_string(cntr) + ".jpg";
	imwrite(savingName, in_frame);
	cout << "PICTURE: " << cntr << " SAVED" << endl;	
}

mavrosCommand::mavrosCommand(){
	_nh = NodeHandle();
	init();
}

mavrosCommand::~mavrosCommand(){
}

void mavrosCommand::init(){
	_rcInSub = _nh.subscribe("mavros/rc/in", 100, &mavrosCommand::rcInputCb, this);
}

void mavrosCommand::rcInputCb(mavros_msgs::RCIn::ConstPtr msg) {
	_rcIn[5] = msg->channels[5];
}

int mavrosCommand::getRCInput(){
	return _rcIn[5];
}
