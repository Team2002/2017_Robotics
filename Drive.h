#ifndef DRIVE_H__INCLUDED	//Make sure this isn't included twice
#define DRIVE_H__INCLUDED

//Include the thing that makes everything work
#include "WPILib.h"

class Drive {
public:
	Drive(void);
	~Drive(void);

	void SetMotors(float, float);
	void StopMotors(void);

private:
	const float LEFT_MOTOR_MULTIPLIER = 0.75;    //Speed multipliers for right and left drive motors
	const float RIGHT_MOTOR_MULTIPLIER = 1;

	Talon *oFrontLeft, *oFrontRight, *oBackLeft, *oBackRight;    //Objects for motors
};

#endif /* DRIVE_H__INCLUDED */
