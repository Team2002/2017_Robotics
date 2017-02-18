/*
 * Fuel.h
 *
 *  Created on: Feb 15, 2017
 *      Author: wasia
 */
#include "WPILib.h"
#ifndef SRC_FUEL_H_
#define SRC_FUEL_H_

class Lift {
public:
	Lift(void);
	~Lift(void);

	void SetMotorsLift(float);
	void StopMotorsLift(void);

private:
	const float SPEED_MOTOR_MULTIPLIER = 0.75;

	Talon *oClimbMotor;    //Objects for motors
};


#endif /* SRC_FUEL_H_ */
