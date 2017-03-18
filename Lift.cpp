#include "Lift.h"
#include "Config.h"

Lift::Lift(void) {
	oClimbMotor = new Talon(PORT_TALON_CLIMB);
}

Lift::~Lift(void) {
	delete oClimbMotor;
}

//Set motor speed
void Lift::StartLiftMotor(void) {
	oClimbMotor->Set(CLIMB_MOTOR_MULTIPLIER);
}

//Slow the motor
void Lift::SlowLiftMotor(void) {
	oClimbMotor->Set(.5);
	Wait(1);
	oClimbMotor->Set(.25);
}
