#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED

// Driver Station Ports
const int PORT_JOYSTICK = 0; // Joysticks

// PWM Ports
const int PORT_TALON_DRIVE_FRONTLEFT = 0; // Talons (Motor Controllers)
const int PORT_TALON_DRIVE_FRONTRIGHT = 3;
const int PORT_TALON_DRIVE_BACKLEFT = 2;
const int PORT_TALON_DRIVE_BACKRIGHT = 5;
//const int PORT_TALON_LIFT_LEFT_UP = -1;
//const int PORT_TALON_LIFT_RIGHT_UP = -1;
//const int PORT_TALON_LIFT_LEFT_DOWN = -1;
//const int PORT_TALON_LIFT_RIGHT_DOWN = -1;
//const int PORT_TALON_LAUNCH = 5;
const int PORT_TALON_INTAKE = 4;
const int PORT_TALON_LIFT = 6; //not really 6 change later

// DIO Ports
const int PORT_LIMIT_SWITCH_LAUNCH = 0; // Limit Switches
const int PORT_LIMIT_SWITCH_INTAKE = 1;

// Relay Ports
const int PORT_RELAY_RED = 0; // Spike H-Bridge Relays (for LEDs)
const int PORT_RELAY_GREEN = 1;
const int PORT_RELAY_BLUE = 2;

// Motor Reversal
const bool DRIVE_MOTOR_FRONTLEFT_REVERSED = false; // Drive
const bool DRIVE_MOTOR_FRONTRIGHT_REVERSED = true;
const bool DRIVE_MOTOR_BACKLEFT_REVERSED = false;
const bool DRIVE_MOTOR_BACKRIGHT_REVERSED = true;

const bool LIFT_MOTOR_LEFT_UP_REVERSED = false; // Lift
const bool LIFT_MOTOR_RIGHT_UP_REVERSED = true;
const bool LIFT_MOTOR_LEFT_DOWN_REVERSED = false;
const bool LIFT_MOTOR_RIGHT_DOWN_REVERSED = true;

const bool INTAKE_MOTOR_REVERSED = true; // Catapult
const bool LAUNCH_MOTOR_REVERSED = true;

// Joystick Setup
const int JOYSTICK_AXIS_LEFT = 1; // Axes
const int JOYSTICK_AXIS_RIGHT = 3;

const int JOYSTICK_BUTTON_REVERSE = 4; // Buttons
const int JOYSTICK_BUTTON_LOCK_TURNING = 6;
const int JOYSTICK_BUTTON_TRACK_TARGET = 5;
const int JOYSTICK_BUTTON_RELEASE_FUEL = 3;
const int JOYSTICK_BUTTON_INTAKE = 1;
const int SPEED_MOTOR_MULTIPLIER = 2;

// New Joystick Buttons that Are Not Correct Yet
const int JOYSTICK_BUTTON_LIFT_UP = 7;
const int JOYSTICK_BUTTON_SLOW_ASCENT = 8;

//const int JOYSTICK_BUTTON_INTAKE_DOWN = 2;
//const int JOYSTICK_BUTTON_FORCE_INTAKE_FORWARD = 9;
//const int JOYSTICK_BUTTON_FORCE_INTAKE_BACK = 10;
//const int JOYSTICK_BUTTON_CAMERA_TOGGLE = 8;
//const int JOYSTICK_BUTTON_LIFT_UP = -1;
//const int JOYSTICK_BUTTON_LIFT_DOWN = -1;
//const int JOYSTICK_BUTTON_LIFT_TOGGLE = -1;


// Shooting
const float LAUNCH_MOTOR_SPEED = 1; // Speed to run motor when shooting

// Camera Settings
const char CAMERA_NAME[] = "cam0\0"; // Found in RoboRio web interface
const int CAMERA_RES_X = 640;
const int CAMERA_RES_Y = 480;
const int CAMERA_FPS = 10;
const unsigned int CAMERA_EXPOSURE = 0;

// Target Tracking
const int TARGET_X = 295; // Target x coordinate
const int TARGET_Y = 420; // Target y coordinate
const float CENTERED_THRESHOLD = 0.04; // Threshold for considering the target centered (CENTERED_THRESHOLD * RES_X/RES_Y = pixels target can be off)
const int STOP_DISTANCE = 100; //Distance between targets when at lift
const float VOLTAGE_1 = 11; // Two points for creating the line that calculates what the motor speed should be during tracking based on battery voltage
const float SPEED_1 = 0.5;
const float VOLTAGE_2 = 13;
const float SPEED_2 = 0.3;
const float SLOPE = (SPEED_2 - SPEED_1) / (VOLTAGE_2 - VOLTAGE_1);

// Other
const float CYCLE_TIME_DELAY = 0.02; // Time to wait between each update cycle in tele-op (to prevent needless CPU usage)

#endif /* CONFIG_H__INCLUDED */
