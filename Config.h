#ifndef CONFIG_H__INCLUDED
#define CONFIG_H__INCLUDED

// Driver Station Ports
const int PORT_JOYSTICK = 0; // Joystick

// PWM Ports
const int PORT_TALON_DRIVE_FRONTLEFT = 2; // Talons (Motor Controllers)
const int PORT_TALON_DRIVE_FRONTRIGHT = 14;
const int PORT_TALON_DRIVE_BACKLEFT = 12;
const int PORT_TALON_DRIVE_BACKRIGHT = 13;
const int PORT_TALON_LAUNCH = 11;
const int PORT_TALON_CLIMB = 16;

// Relay Ports
const int PORT_RELAY_RED = 0; // Spike H-Bridge Relays (for LEDs)
const int PORT_RELAY_GREEN = 1;
const int PORT_RELAY_BLUE = 2;

// Motor Reversal
const bool DRIVE_MOTOR_FRONTLEFT_REVERSED = false; // Drive
const bool DRIVE_MOTOR_FRONTRIGHT_REVERSED = true;
const bool DRIVE_MOTOR_BACKLEFT_REVERSED = false;
const bool DRIVE_MOTOR_BACKRIGHT_REVERSED = true;

const bool LAUNCH_MOTOR_REVERSED = true; // Launch
const bool CLIMB_MOTOR_REVERSED = true; // Climb

// Motor Speed
const float LEFT_MOTOR_MULTIPLIER = 1;
const float RIGHT_MOTOR_MULTIPLIER = 1;
const float CLIMB_MOTOR_MULTIPLIER = 1;
const float LAUNCH_MOTOR_MULTIPLIER = 1;

// Joystick Setup
const int JOYSTICK_AXIS_LEFT = 1; // Axes
const int JOYSTICK_AXIS_RIGHT = 3;

const int JOYSTICK_BUTTON_REVERSE = -1; // Buttons
const int JOYSTICK_BUTTON_LOCK_TURNING = -1;
const int JOYSTICK_BUTTON_TRACK_TARGET = -1;
const int JOYSTICK_BUTTON_LAUNCH = -1;
const int JOYSTICK_BUTTON_CLIMB = -1;
const int JOYSTICK_BUTTON_STOP_CLIMB = -1;

// Camera Settings
const char CAMERA_NAME[] = "cam0\0"; // Found in RoboRio web interface
const int CAMERA_RES_X = 640;
const int CAMERA_RES_Y = 480;
const int CAMERA_FPS = 10;

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
