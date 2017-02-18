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
void Lift::SetMotorsLift(void) {
	oClimbMotor->Set(1); // may change the speed of this later
}

//Stop the motors
void Lift::SlowMotorsLift(void) {
	oClimbMotor->Set(.5);
	Wait(1);
	oClimbMotor->Set(.25);
}
