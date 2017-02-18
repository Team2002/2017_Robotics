#ifndef ROBOT_H__INCLUDED	//Make sure this isn't included twice
#define ROBOT_H__INCLUDED

#include "WPILib.h"
#include "opencv2/core/core.hpp"
#include "NetworkTables/NetworkTable.h"
#include "Drive.h"
#include "LED.h"
#include "GripPipeline.h"
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

	Joystick *oJoystick;	//Prepending "o" to avoid naming conflicts ("o" for object)
	LED *oLED;
	Drive *oDrive;

	Preferences *oPrefs;
	int autonomousMode;

	//For vision tracking
	cs::UsbCamera *oUSBCamera;
	//USBCamera *oUSBCameraBack;
	//Image *oImage;
	//NetworkTable *oNetworkTable;
	NetworkTable *oTable;
};

#endif /* ROBOT_H__INCLUDED */
