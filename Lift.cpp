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
	if(CLIMB_MOTOR_REVERSED)
		oClimbMotor->Set(-CLIMB_MOTOR_MULTIPLIER);
	else
		oClimbMotor->Set(CLIMB_MOTOR_MULTIPLIER);
}

//Slow the motor
void Lift::SlowLiftMotor(void) {
	if(CLIMB_MOTOR_REVERSED)
		oClimbMotor->Set(-.5 * CLIMB_MOTOR_MULTIPLIER);
	else
		oClimbMotor->Set(.5 * CLIMB_MOTOR_MULTIPLIER);

}

void Lift::StopLiftMotor(void) {
	oClimbMotor->Set(0);
}
