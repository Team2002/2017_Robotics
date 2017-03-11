#include "Lift.h"
#include "Config.h"

//Constructor
Lift::Lift(void) {
	oClimbMotor = new Talon(PORT_TALON_LIFT); //change PORT to whatever port we're using
}

//Destructor
Lift::~Lift(void) {
	delete oClimbMotor;
}

//Set motor speed
void Lift::SetMotorsLift(float liftButton) {
	liftButton *= SPEED_MOTOR_MULTIPLIER;

	if(DRIVE_MOTOR_LIFT_UP) //change variable (make button start)
		oClimbMotor->Set(liftButton);
	else
		oClimbMotor->Set(0);

	if(DRIVE_MOTOR_LIFT_STOP) //change variable (make button stop)
		oClimbMotor->Set(0);
	else
		oClimbMotor->Set(liftButton);
	if(DRIVE_MOTOR_LIFT_FINAL_STOP) //change variable (make button stop for the final)
		oClimbMotor->Set((liftButton/(4)));
	else
		oClimbMotor->Set(liftButton);
}

//Stop the motors
void Lift::StopMotorsLift(void) {
	oClimbMotor->Set(0);
}



