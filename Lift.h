#ifndef SRC_LIFT_H_
#define SRC_LIFT_H_
//Include the thing that makes everything work
#include "WPILib.h"

class Lift {
public:
	Lift(void);
	~Lift(void);

	void SetMotorsLift(void);
	void SlowMotorsLift(void);

private:
	const float SPEED_MOTOR_MULTIPLIER = 0.75;

	Talon *oClimbMotor;    //Objects for motors
};

#endif /* SRC_LIFT_H_ */
