#include "Robot.h"
#include "Config.h"
#include "GripPipeline.h"

//Constructor
Robot::Robot(void) {
	oJoystick = new Joystick(PORT_JOYSTICK);
	oLED = new LED();
	oDrive = new Drive();
	oLift = new Lift();
	
	oPrefs = nullptr;
	autonomousMode = 0;
  
  oNetworkTable = &*NetworkTable::GetTable("GRIP/targets"); // GetTable returns a shared pointer, so referencing and dereferencing converts it to a raw pointer
}

//Destructor
Robot::~Robot(void) {
	delete oJoystick;
	delete oLED;
	delete oDrive;
  
  delete oNetworkTable;
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

	// Camera settings
	//oUSBCamera->SetFPS(CAMERA_FPS);
	//oUSBCamera->SetResolution(CAMERA_RES_X, CAMERA_RES_Y);
	//oUSBCameraFront->SetExposureManual(CAMERA_0_EXPOSURE);
	//oUSBCameraFront->UpdateSettings();
	//oUSBCameraBack->SetFPS(CAMERA_FPS);
	//oUSBCameraBack->SetSize(CAMERA_RES_X, CAMERA_RES_Y);
	//oUSBCameraBack->SetBrightness(CAMERA_1_BRIGHTNESS);
	//oUSBCameraBack->SetExposureAuto();
	//oUSBCameraBack->UpdateSettings();
}

// Use Test mode to charge the catapult
void Robot::Test(void) {
	/*oCatapult->SetCharging();
	 while(IsTest() && IsEnabled()){
	 oCatapult->CheckCatapult();
	 Wait(CYCLE_TIME_DELAY);
	 }*/
  oDrive->SetMotors(1,1);
}

//Autonomous mode
void Robot::Autonomous(void) {
	//Load preferences
		oPrefs = Preferences::GetInstance();
		autonomousMode = oPrefs->GetInt("Autonomous", 0);
	bool failed = false;
	switch(autonomousMode) {
		case 1:		//Left
			//move forward
			//turn right
			//find lift
			break;

		case 2:		//Middle
			//move forward
			//find lift
			break;

		case 3:		//Right
			//move forward
			//turn left
			//find lift
			break;

		default:	//Nonsense value
			SmartDashboard::PutNumber("Autonomous Error: ", autonomousMode);
			failed = true;
			break;
	}
	if(!failed) {
		//line up to lift
		//put gear on
	}
}

//Tele-op
void Robot::OperatorControl(void) {
	float speedLeft, speedRight;		// Drive motor speeds for manual control
	bool reversed = false,				// Keeps track of robot being in reverse mode
		reverseButtonPressed = false;	// Needed for toggling reverse mode
	std::vector<double> coord;			// Target coordinates sent from GRIP
	//grip::GripPipeline grip();			//Grip object
	//cv::Mat frame;						//Image
	//cv::VideoCapture camera;			//Camera

	//camera.set(CV_CAP_PROP_FRAME_WIDTH, CAMERA_RES_X);
	//camera.set(CV_CAP_PROP_FRAME_HEIGHT, CAMERA_RES_Y);

	
	// Continue updating robot while in tele-op mode
	while(IsOperatorControl() && IsEnabled()) {

		// For camera calibrating, sends target data to smart dashboard
		//camera.read(frame);
		//grip.GripPipeline::Process(frame);
		coord = oNetworkTable->GetNumberArray("centerX", std::vector<double>());
		//coord = grip.GripPipeline::GetConvexHullsOutput();
		SmartDashboard::PutNumber("Empty: ", (double)coord.empty());
		if(!coord.empty()) {
			SmartDashboard::PutNumber("BLOBS X: ", coord[0]);
			SmartDashboard::PutNumber("BLOBS Y: ", coord[1]);
		}
		/*
		// Autonomous target tracking
		if(oJoystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET)) {
			
			// Calculate drive motor speed based on battery voltage
			float voltage = DriverStation::GetInstance().GetBatteryVoltage();
			float speed = SLOPE * voltage + (SPEED_1 - (SLOPE * VOLTAGE_1));
			SmartDashboard::PutNumber("VOLTAGE: ", voltage);
			SmartDashboard::PutNumber("SPEED: ", speed);
			
			// Get targets coordinates from the network table (return empty vector if network table is unreachable)
			//coord = oNetworkTable->GetNumberArray("centerX", std::vector<double>());
			
			// Make sure the network table returned values
			if(!coord.empty()) {
				
				// First correct robot orientation (x axis on image)...
				if(coord[0] < TARGET_X - (CENTERED_THRESHOLD * CAMERA_RES_X))
					oDrive->SetMotors(-speed, speed);
				else if(coord[0] > TARGET_X + (CENTERED_THRESHOLD * CAMERA_RES_X))
					oDrive->SetMotors(speed, -speed);
				else {
					
					// ...then correct robot distance to target (y axis on image)
					if(coord[1] < TARGET_Y - (CENTERED_THRESHOLD * CAMERA_RES_Y))
						oDrive->SetMotors(speed, speed);
					else if(coord[1] > TARGET_Y + (CENTERED_THRESHOLD * CAMERA_RES_Y))
						oDrive->SetMotors(-speed, -speed);
					else {
						
						// Robot is on target, stop robot and make sure it is still on target
						oDrive->StopMotors(); // Stop motors
						Wait(0.5); // Wait for robot to stop moving
						if(abs(coord[0] - TARGET_X) < (CENTERED_THRESHOLD * CAMERA_RES_X) && abs(coord[1] - TARGET_Y) < (CENTERED_THRESHOLD * CAMERA_RES_Y)) {
							//put gear on
						}
					}
				}
			}

			// If the network table did not return values, stop drive motors
			else {
				oDrive->StopMotors();
			}
		}

		// Manual driver control
		else {
			
			// Reset auto target tracking variable
			//firingCatapult = false;
			
			// Get joystick values (negated because the stupid driver station reads them that way)
			speedLeft = -oJoystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
			speedRight = -oJoystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);
			
			// Turn locking. Forces all motors to go the same speed.
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_LOCK_TURNING))
				speedLeft = speedRight;
			
			// Reverse mode toggling
			ToggleBool(oJoystick->GetRawButton(JOYSTICK_BUTTON_REVERSE), reverseButtonPressed, reversed);
			if(reversed) {
				float speedLeftTemp = speedLeft;
				speedLeft = -speedRight;
				speedRight = -speedLeftTemp;
			}
			
			// Set drive motors
			oDrive->SetMotors(speedLeft, speedRight);
			
			// Robot Lift Mechanism
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_LIFT_UP))
				oLift->SetMotorsLift();
			else if(oJoystick->GetRawButton(JOYSTICK_BUTTON_SLOW_ASCENT))
				oLift->SlowMotorsLift();

			// Boulder intake piston
			//if(oJoystick->GetRawButton(JOYSTICK_BUTTON_INTAKE_DOWN))
				; //oCatapult->SetIntakeState(Catapult::DOWN);
			else if(oJoystick->GetRawButton(JOYSTICK_BUTTON_INTAKE_UP))
				oDrive->SetMotors(1, 1); //oCatapult->SetIntakeState(Catapult::UP);
				
			// Boulder intake wheels
			//if(oJoystick->GetRawButton(JOYSTICK_BUTTON_FORCE_INTAKE_FORWARD))
				; //oCatapult->ForceIntakeWheels(Catapult::FORWARD);
			//else if(oJoystick->GetRawButton(JOYSTICK_BUTTON_FORCE_INTAKE_BACK))
				; //oCatapult->ForceIntakeWheels(Catapult::BACK);
			//else
				; //oCatapult->ForceIntakeWheels(Catapult::OFF);
				
			// Fire boulder
			//if(oJoystick->GetRawButton(JOYSTICK_BUTTON_FIRE_BOULDER))
				; //oCatapult->SetLaunchState(Catapult::FIRE);
		}
		
		// Check if the catapult needs to do anything
		//oCatapult->CheckCatapult();
		
		// Wait until next cycle (to prevent needless CPU usage)

		*/Wait(CYCLE_TIME_DELAY);
	}
	
	// Stop drive motors
	oDrive->StopMotors();
	
	// Stop camera
	//oUSBCameraFront->StopCapture();
	//oUSBCameraBack->StopCapture();
}

/*
 This function allows a boolean to be toggled with a joystick button, inside of a while loop that is constantly updating.
 button:        Joystick button for toggling.
 buttonPressed: Boolean for tracking whether the button was pressed in the last cycle. This prevents toggleBool from rapidly switching states while the joystick button is held down.
 toggleBool:    Boolean to be toggled.
 */
void Robot::ToggleBool(bool button, bool &buttonPressed, bool &toggleBool) {
	if(button && !buttonPressed) {
		buttonPressed = true;
		toggleBool = !toggleBool;
	} else if(!button)
		buttonPressed = false;
}

START_ROBOT_CLASS(Robot);
