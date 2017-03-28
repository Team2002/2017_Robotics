#include "Drive.h"
#include "Config.h"

//Constructor
Drive::Drive(void) {
	oFrontLeft = new Talon(PORT_TALON_DRIVE_FRONTLEFT);
	oFrontRight = new Talon(PORT_TALON_DRIVE_FRONTRIGHT);
	oBackLeft = new Talon(PORT_TALON_DRIVE_BACKLEFT);
	oBackRight = new Talon(PORT_TALON_DRIVE_BACKRIGHT);
}

//Destructor
Drive::~Drive(void) {
	delete oFrontLeft;
	delete oFrontRight;
	delete oBackLeft;
	delete oBackRight;
}

//Set motor speed
void Drive::SetMotors(float left, float right) {
	left *= LEFT_MOTOR_MULTIPLIER;
	right *= RIGHT_MOTOR_MULTIPLIER;
	SmartDashboard::PutNumber("Left: ", left);
	SmartDashboard::PutNumber("Right: ", right);

	if(DRIVE_MOTOR_FRONTLEFT_REVERSED)
		oFrontLeft->Set(-left);
	else
		oFrontLeft->Set(left);
	
	if(DRIVE_MOTOR_FRONTRIGHT_REVERSED)
		oFrontRight->Set(-right);
	else
		oFrontRight->Set(right);
	
	if(DRIVE_MOTOR_BACKLEFT_REVERSED)
		oBackLeft->Set(-left);
	else
		oBackLeft->Set(left);
	
	if(DRIVE_MOTOR_BACKRIGHT_REVERSED)
		oBackRight->Set(-right);
	else
		oBackRight->Set(right);
}

//Stop the motors
void Drive::StopMotors(void) {
	oFrontLeft->StopMotor();
	oFrontRight->StopMotor();
	oBackLeft->StopMotor();
	oBackRight->StopMotor();
}
