#include "Robot.h"
#include "Config.h"
#include <iostream>
#include "NetworkTables/NetworkTable.h"

//Constructor
Robot::Robot(void) {
	oJoystick = new Joystick(PORT_JOYSTICK);
	oLED = new LED();
	oDrive = new Drive();
	
	oPrefs = nullptr;
	autonomousMode = 0;

	oUSBCamera = new cs::UsbCamera(CAMERA_NAME_FRONT, 0);
	//oUSBCameraBack = new USBCamera(CAMERA_NAME_BACK, true);
	//oImage = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	oTable = &*NetworkTable::GetTable("GRIP/Target");
	//oNetworkTable = &*NetworkTable::GetTable("datatable"); // GetTable returns a shared pointer, so referencing and dereferencing converts it to a raw pointer

}

//Destructor
Robot::~Robot(void) {
	delete oJoystick;
	delete oLED;
	delete oDrive;
	
	//delete oUSBCameraFront;
	//delete oUSBCameraBack;
	//delete oImage;
	delete oTable;
	//delete oNetworkTable;
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
	//oUSBCameraFront->SetFPS(CAMERA_FPS);
	//oUSBCameraFront->SetResolution(CAMERA_RES_X, CAMERA_RES_Y);
	//oUSBCameraFront->SetExposureManual(CAMERA_0_EXPOSURE);
	//oUSBCameraFront->UpdateSettings();
	
	//oUSBCameraBack->SetFPS(CAMERA_FPS);
	//oUSBCameraBack->SetSize(CAMERA_RES_X, CAMERA_RES_Y);
	//oUSBCameraBack->SetBrightness(CAMERA_1_BRIGHTNESS);
	//oUSBCameraBack->SetExposureAuto();
	//oUSBCameraBack->UpdateSettings();

	//Load preferences
	oPrefs = Preferences::GetInstance();
	autonomousMode = oPrefs->GetInt("Autonomous", 0);

	/* Set up camera
	CameraServer::GetInstance()->StartAutomaticCapture();
	oUSBCamera->SetResolution(CAMERA_RES_X, CAMERA_RES_Y);
	*/
}

// Use Test mode to charge the catapult
void Robot::Test(void) {
	/*oCatapult->SetCharging();
	 while(IsTest() && IsEnabled()){
	 oCatapult->CheckCatapult();
	 Wait(CYCLE_TIME_DELAY);
	 }*/
}

//Autonomous mode
void Robot::Autonomous(void) {
	oDrive->SetMotors(1, 1);
	Wait(3.5);
	oDrive->SetMotors(0, 0);
}

//Tele-op
void Robot::OperatorControl(void) {
	float speedLeft, speedRight,		// Drive motor speeds for manual control
		speedLeftTemp;					// Temporarily used for reversing drive motor speeds
	//bool firingCatapult = false;		// Needed to prevent robot from moving while auto shooting the boulder
	bool reversed = false,				// Keeps track of robot being in reverse mode
		reverseButtonPressed = false;	// Needed for toggling reverse mode
	int camera = 0;						// Keeps track of which camera is currently in use (0 = front, 1 = back)
	std::vector<double> coord;			// Target coordinates sent from RoboRealm
	cs::CvSink in = CameraServer::GetInstance()->GetVideo();
	cs::CvSource out = CameraServer::GetInstance()->PutVideo(CAMERA_NAME_FRONT, CAMERA_RES_X, CAMERA_RES_Y);
	cv::Mat image;
	CameraServer::GetInstance()->StartAutomaticCapture();
	// Start camera
	//oUSBCamera->StartAutomaticCapture();
	//oUSBCameraBack->StartCapture();
	
	// Continue updating robot while in tele-op mode
	while(IsOperatorControl() && IsEnabled()) {
		//in.GrabFrame(image);
		//out.PutFrame(image);
		
		// For camera calibrating, sends target data to smart dashboarad
		/*coord = oNetworkTable->GetNumberArray("BLOBS", std::vector<double>());
		if(!coord.empty()) {
			SmartDashboard::PutNumber("BLOBS X: ", coord[0]);
			SmartDashboard::PutNumber("BLOBS Y: ", coord[1]);
		}
		*/
		// Autonomous target tracking
		if(oJoystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET) /*&& !firingCatapult*/&& camera == 0) {
			
			// Calculate drive motor speed based on battery voltage
			float voltage = DriverStation::GetInstance().GetBatteryVoltage();
			float speed = SLOPE * voltage + (SPEED_1 - (SLOPE * VOLTAGE_1));
			SmartDashboard::PutNumber("VOLTAGE: ", voltage);
			SmartDashboard::PutNumber("SPEED: ", speed);
			
			// Get targets coordinates from the network table (return empty vector if network table is unreachable)
			//coord = oNetworkTable->GetNumberArray("BLOBS", std::vector<double>());
			
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
						if(coord[0] >= TARGET_X - (CENTERED_THRESHOLD * CAMERA_RES_X) && coord[0] <= TARGET_X + (CENTERED_THRESHOLD * CAMERA_RES_X) && coord[1] >= TARGET_Y - (CENTERED_THRESHOLD * CAMERA_RES_Y) && coord[1] <= TARGET_Y + (CENTERED_THRESHOLD * CAMERA_RES_Y)) {
							//oCatapult->SetLaunchState(Catapult::FIRE); // Fire boulder
							//firingCatapult = true; // Prevents robot from trying to re-adjust while firing the boulder
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
		else if(!oJoystick->GetRawButton(JOYSTICK_BUTTON_TRACK_TARGET)) {
			
			// Reset auto target tracking variable
			//firingCatapult = false;
			
			// Camera toggling
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_CAMERA_TOGGLE))
				camera = 1;
			else
				camera = 0;
			
			// Get joystick values (negated because the stupid driver station reads them that way)
			speedLeft = -oJoystick->GetRawAxis(JOYSTICK_AXIS_LEFT);
			speedRight = -oJoystick->GetRawAxis(JOYSTICK_AXIS_RIGHT);
			
			// Turn locking. Forces all motors to go the same speed.
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_LOCK_TURNING))
				speedLeft = speedRight;
			
			// Reverse mode toggling
			ToggleBool(oJoystick->GetRawButton(JOYSTICK_BUTTON_REVERSE), reverseButtonPressed, reversed);
			if(reversed) {
				speedLeftTemp = speedLeft;
				speedLeft = -speedRight;
				speedRight = -speedLeftTemp;
			}
			
			// Set drive motors
			oDrive->SetMotors(speedLeft, speedRight);
			
			// Boulder intake piston
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_INTAKE_DOWN))
				; //oCatapult->SetIntakeState(Catapult::DOWN);
			else if(oJoystick->GetRawButton(JOYSTICK_BUTTON_INTAKE_UP))
				oDrive->SetMotors(1,1); //oCatapult->SetIntakeState(Catapult::UP);
				
			// Boulder intake wheels
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_FORCE_INTAKE_FORWARD))
				; //oCatapult->ForceIntakeWheels(Catapult::FORWARD);
			else if(oJoystick->GetRawButton(JOYSTICK_BUTTON_FORCE_INTAKE_BACK))
				; //oCatapult->ForceIntakeWheels(Catapult::BACK);
			else
				; //oCatapult->ForceIntakeWheels(Catapult::OFF);
				
			// Fire boulder
			if(oJoystick->GetRawButton(JOYSTICK_BUTTON_FIRE_BOULDER))
				; //oCatapult->SetLaunchState(Catapult::FIRE);
		}
		
		// Check if the catapult needs to do anything
		//oCatapult->CheckCatapult();
		
		// Wait until next cycle (to prevent needless CPU usage)
		Wait(CYCLE_TIME_DELAY);
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
