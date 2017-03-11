#ifndef ROBOT_H__INCLUDED
#define ROBOT_H__INCLUDED

#include "WPILib.h"
#include "opencv2/core/core.hpp"
#include "NetworkTables/NetworkTable.h"
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>
#include "Drive.h"
#include "Lift.h"
#include "LED.h"
//#include "USBCamera.cpp"

class Robot: public SampleRobot {
public:
	Robot(void);
	~Robot(void);

	void RobotInit(void);
	void Test(void);
	void Autonomous(void);
	void OperatorControl(void);

private:
	void ToggleBool(bool, bool&, bool&);
  
	Joystick *oJoystick; //Prepending "o" to avoid naming conflicts ("o" for object)
	LED *oLED;
	Drive *oDrive;
	Lift *oLift;

	Preferences *oPrefs;
	int autonomousMode;

	Preferences *oPrefs;
	int autonomousMode;

	Preferences *oPrefs;

	//For vision tracking
	cs::UsbCamera *oUSBCamera;
	//cv::VideoCapture *oCamera;
	//Image *oImage;
	std::shared_ptr<NetworkTable> oNetworkTable;
};

#endif /* ROBOT_H__INCLUDED */
