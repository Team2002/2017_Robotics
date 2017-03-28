#include "Robot.h"
#include "Config.h"

//Constructor
Robot::Robot(void) {
	oJoystick = new Joystick(PORT_JOYSTICK);
	oLED = new LED();
	oDrive = new Drive();
	oLaunch = new Launch();
	oLift = new Lift();
	
	oPrefs = nullptr;

	oUSBCamera = new cs::UsbCamera(CAMERA_NAME, true);
	oNetworkTable = NetworkTable::GetTable("RoboRealm"); // GetTable returns a shared pointer
}

//Destructor
Robot::~Robot(void) {
	delete oJoystick;
	delete oLED;
	delete oDrive;
	delete oLaunch;
	delete oLift;
	
	delete oUSBCamera;
}

//Initialize robot
void Robot::RobotInit(void) {
	// Turn on the LEDs based on what alliance we are on
	/*switch(DriverStation::GetInstance().GetAlliance()){
	 case DriverStation::kRed:
	 oLED->ChangeColor(LED::Red);
	 break;
	 case DriverStation::kBlue:
	 oLED->ChangeColor(LED::Blue);
	 break;
	 case DriverStation::kInvalid:
	 default:
	 oLED->ChangeColor(LED::White);
	 break;
	 }*/
CameraServer*test= CameraServer::GetInstance();
	// Camera settings
	oUSBCamera->SetFPS(CAMERA_FPS);
	oUSBCamera->SetResolution(CAMERA_RES_X, CAMERA_RES_Y);
	oUSBCamera->SetBrightness(50);
	oUSBCamera->SetExposureManual(0);
	test->StartAutomaticCapture(*oUSBCamera);

}

// Use Test mode to charge the catapult
void Robot::Test(void) {
	/*oCatapult->SetCharging();
	 while(IsTest() && IsEnabled()){
	 oCatapult->CheckCatapult();
	 Wait(CYCLE_TIME_DELAY);
	 }*/
	oDrive->SetMotors(1, 1);
}

//Autonomous mode
void Robot::Autonomous(void) {
	//Load preferences
	oPrefs = Preferences::GetInstance();
	//int autonomousMode = oPrefs->GetInt("Auto", 0);
	SmartDashboard::PutNumber("Autonomous Error: ", 0.1);

	//Variables
	std::vector<double> coord;
	//float center = -1;
	//bool onTarget = false,
	//	 failed = false;

	//Move forward
	oDrive->SetMotors(1, 1);
	Wait(2.5);
	/*
	 switch(autonomousMode) {
	 case 1:		//Left
	 //Turn right
	 oDrive->SetMotors(.25, 0);
	 break;

	 case 2:		//Middle
	 break;

	 case 3:		//Right
	 //Turn left
	 oDrive->SetMotors(0, .25);
	 break;

	 default:	//Nonsense value
	 SmartDashboard::PutNumber("Autonomous Error: ", autonomousMode);
	 failed = true;
	 break;
	 }
	 if(!failed) {
	 //Find lift
	 while(center < 0 && IsAutonomous()) {
	 GetVision(coord, center);
	 }
	 oDrive->StopMotors();

	 //Line up to lift
	 int notDone = 2;
	 while(notDone && IsAutonomous()) {
	 GetVision(coord, center);
	 AutoTarget(coord, center, onTarget);
	 if(onTarget)
	 notDone--;
	 else
	 notDone = 2;
	 }
	 }*/oDrive->StopMotors();
}

//Tele-op
void Robot::OperatorControl(void) {
	float speedLeft, speedRight,		//Drive motor speeds for manual control
		center;							//Target for auto aim thing
	bool reversed = false,			//Keeps track of robot being in reverse mode
		reverseButtonPressed = false,	//Needed for toggling reverse mode
		launching = false,				//If launch motor should be on
		launchButtonPressed = false,	//Needed for toggling launch motor
		climbButtonPressed = false,		//If climbing button has been pressed
		onTarget = false;		//Whether the robot is going towards the gear
	std::vector<double> coord;			//Target coordinates sent from GRIP
	
	// Continue updating robot while in tele-op mode
	while(IsOperatorControl() && IsEnabled()) {

		// Autonomous target tracking
		GetVision(coord, center);
		if(oJoystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET))
			AutoTarget(coord, center, onTarget);

		// Manual driver control
		else {

			// Reset auto target tracking variable
			onTarget = false;

			// Get joystick values (negated because the stupid driver station reads them that way)
			speedLeft = -oJoystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
			speedRight = -oJoystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);

			// Turn locking. Forces all motors to go the same speed.
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_LOCK_TURNING))
				speedLeft = speedRight;

			// Reverse mode toggling
			ToggleBool(oJoystick->GetRawButton(JOYSTICK_BUTTON_REVERSE), reversed, reverseButtonPressed);
			if(reversed) {
				float temp = speedLeft;
				speedLeft = -speedRight;
				speedRight = -temp;
			}

			// Set drive motors
			oDrive->SetMotors(speedLeft, speedRight);

			//Launch fuel
			ToggleBool(oJoystick->GetRawButton(JOYSTICK_BUTTON_LAUNCH), launching, launchButtonPressed);
			if(launching)
				oLaunch->SetLaunchMotor();
			else
				oLaunch->StopLaunchMotor();

			//Lift
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_CLIMB)) {
				climbButtonPressed = true;
				oLift->StartLiftMotor();
			} else if(climbButtonPressed)
				oLift->SlowLiftMotor();

			//Stop lift
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_STOP_CLIMB)) {
				climbButtonPressed = false;
				oLift->StopLiftMotor();
			}
		}

		// Wait until next cycle (to prevent needless CPU usage)
		Wait(CYCLE_TIME_DELAY);
	}

	// Stop drive motors
	oDrive->StopMotors();
}

void Robot::GetVision(std::vector<double> &coord, float &center) {

	// For camera calibrating, sends target data to smart dashboard
	coord = oNetworkTable->GetNumberArray("BLOBS", std::vector<double>());
	SmartDashboard::PutNumber("Empty: ", (double) coord.empty());

	//Make sure RoboRealm returned exactly 2 targets
	if(coord.size() == 4) {
		SmartDashboard::PutNumber("Blob1 X: ", coord[0]);
		SmartDashboard::PutNumber("Blob2 X: ", coord[2]);
		center = (coord[0] + coord[2]) / 2;
		SmartDashboard::PutNumber("Center: ", center);
	}
}

void Robot::AutoTarget(std::vector<double> &coord, float &center, bool &onTarget) {

	// Calculate drive motor speed based on battery voltage
	float voltage = DriverStation::GetInstance().GetBatteryVoltage();
	float speed = SLOPE * voltage + (SPEED_1 - (SLOPE * VOLTAGE_1));
	SmartDashboard::PutNumber("VOLTAGE: ", voltage);
	SmartDashboard::PutNumber("SPEED: ", speed);

	// Make sure the network table returned values
	if(coord.size() == 4) {

		// First correct robot orientation (x axis on image)...
		if(center < TARGET_X - (CENTERED_THRESHOLD * CAMERA_RES_X)) {
			oDrive->SetMotors(-speed, speed);
			onTarget = false;
		} else if(center > TARGET_X + (CENTERED_THRESHOLD * CAMERA_RES_X)) {
			oDrive->SetMotors(speed, -speed);
			onTarget = false;
		} else {

			/* ...then correct robot distance to target (y axis on image)
			 if(coord[1] < TARGET_Y - (CENTERED_THRESHOLD * CAMERA_RES_Y))
			 oDrive->SetMotors(speed, speed);
			 else if(coord[1] > TARGET_Y + (CENTERED_THRESHOLD * CAMERA_RES_Y))
			 oDrive->SetMotors(-speed, -speed);
			 else {*/

			// Robot is on target, stop robot and make sure it is still on target
			if(!onTarget) {
				onTarget = true;
				oDrive->StopMotors(); // Stop motors
				Wait(0.5); // Wait for robot to stop moving
			} else if(abs(center - TARGET_X) < (CENTERED_THRESHOLD * CAMERA_RES_X)) {
				//Put gear on
				oDrive->SetMotors(speed, speed);
				if(abs(coord[0] - coord[2]) > STOP_DISTANCE) {
					oDrive->StopMotors();
				}
			}
		}
	}

	// If the network table did not return values, stop drive motors
	else {
		oDrive->StopMotors();
	}

}

/*
 This function allows a boolean to be toggled with a joystick button, inside of a while loop that is constantly updating.
 button:        Joystick button for toggling.
 toggleBool:    Boolean to be toggled.
 buttonPressed: Boolean for tracking whether the button was pressed in the last cycle. This prevents toggleBool from rapidly switching states while the joystick button is held down.
 */
void Robot::ToggleBool(bool button, bool &toggleBool, bool &buttonPressed) {
	if(button && !buttonPressed) {
		buttonPressed = true;
		toggleBool = !toggleBool;
	} else if(!button)
		buttonPressed = false;
}

START_ROBOT_CLASS(Robot);
