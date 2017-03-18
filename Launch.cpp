#include "Launch.h"
#include "Config.h"

Launch::Launch(void) {
	oLaunchMotor = new Talon(PORT_TALON_LAUNCH);
}

Launch::~Launch(void) {
	delete oLaunchMotor;
}

//Set motor speed
void Launch::SetLaunchMotor(void) {
	oLaunchMotor->Set(LAUNCH_MOTOR_MULTIPLIER);
}

//Stop the motors
void Launch::StopLaunchMotor(void) {
	oLaunchMotor->Set(0);
}
