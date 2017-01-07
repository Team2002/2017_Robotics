#ifndef ROBOT_H__INCLUDED	//Make sure this isn't included twice
#define ROBOT_H__INCLUDED

#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"
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

	Joystick *oJoystick;	//Prepending "o" to avoid naming conflicts ("o" for object)
	LED *oLED;
	Drive *oDrive;

	//For vision tracking
	USBCamera *oUSBCameraFront;
	USBCamera *oUSBCameraBack;
	Image *oImage;
	NetworkTable *oNetworkTable;
	
};

#endif /* ROBOT_H__INCLUDED */
