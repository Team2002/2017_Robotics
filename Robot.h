#ifndef ROBOT_H__INCLUDED
#define ROBOT_H__INCLUDED

#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>
#include "Drive.h"
#include "LED.h"

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

	Preferences *oPrefs;
	int autonomousMode;

	//For vision tracking
	//cs::UsbCamera *oUSBCamera;
	//cv::VideoCapture *oCamera;
	//Image *oImage;
	NetworkTable *oNetworkTable;
};

#endif /* ROBOT_H__INCLUDED */
