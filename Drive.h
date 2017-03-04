#ifndef DRIVE_H__INCLUDED
#define DRIVE_H__INCLUDED

#include "WPILib.h"

class Drive {
public:
	Drive(void);
	~Drive(void);

	void SetMotors(float, float);
	void StopMotors(void);

private:
	const float RIGHT_MOTOR_MULTIPLIER = 1; //Speed multipliers for right and left drive motors
  const float LEFT_MOTOR_MULTIPLIER = 1;

	Talon *oFrontLeft, *oFrontRight, *oBackLeft, *oBackRight; //Objects for motors
};

#endif /* DRIVE_H__INCLUDED */
