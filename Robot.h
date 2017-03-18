#ifndef ROBOT_H__INCLUDED
#define ROBOT_H__INCLUDED

#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/core/core.hpp>
#include "LED.h"
#include "Drive.h"
#include "Launch.h"
#include "Lift.h"

class Robot: public SampleRobot {
public:
	Robot(void);
	~Robot(void);

	void RobotInit(void);
	void Test(void);
	void Autonomous(void);
	void OperatorControl(void);

private:
	void GetVision(std::vector<double>&, float&);
	void AutoTarget(std::vector<double>&, float&, bool&);
	void ToggleBool(bool, bool&, bool&);

	Joystick *oJoystick; //Prepending "o" to avoid naming conflicts ("o" for object)
	LED *oLED;
	Drive *oDrive;
	Launch *oLaunch;
	Lift *oLift;

	Preferences *oPrefs;

	//For vision tracking
	cs::UsbCamera *oUSBCamera;
	//cv::VideoCapture *oCamera;
	//Image *oImage;
	std::shared_ptr<NetworkTable> oNetworkTable;
};

#endif /* ROBOT_H__INCLUDED */
