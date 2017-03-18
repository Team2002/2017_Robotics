#include "Fuel.h"
#include "Config.h"

Fuel::Fuel(void) {
	oLaunchMotor = new Talon(PORT_TALON_LAUNCH);
}

Fuel::~Fuel(void) {
	delete oLaunchMotor;
}

//Set motor speed
void Fuel::SetLaunchMotor(void) {
	oLaunchMotor->Set(1);
}

//Stop the motors
void Fuel::StopLaunchMotor(void) {
	oLaunchMotor->Set(0);
}
