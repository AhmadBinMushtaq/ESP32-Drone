#ifndef CONSTANTS_H
#define CONSTANTS_H

// average flight time is 13 minutes with 10x5 props, 3000 mAh 3S lipo battery

//----------- PINS -----------
#define FRONT_LEFT_MOTOR_PIN 13
#define FRONT_RIGHT_MOTOR_PIN 12
#define REAR_LEFT_MOTOR_PIN 14
#define REAR_RIGHT_MOTOR_PIN 27
#define LED_PIN 4
#define BUZZER_PIN 15
#define IMU_INTERRUPT_PIN 19
#define IMU_LED_PIN 2
#define RX_INTERRUPT_PIN 33

//----------- IMU CALIBRATION -----------
#define ACCEL_OFFSET_X 90
#define ACCEL_OFFSET_Y 1611
#define ACCEL_OFFSET_Z 1788
#define GYRO_OFFSET_X 220
#define GYRO_OFFSET_Y 76
#define GYRO_OFFSET_Z -86

//----------- RECEIVER & TRANSMITTER -----------
#define TRANSMITTER_JOYSTICK_MIN_VALUE 600
#define TRANSMITTER_JOYSTICK_MAX_VALUE 1600
#define TRANSMITTER_ARMING_DURATION_IN_MILLISECONDS 2000
#define TRANSMITTER_ARMING_JOYSTICK_TOLERANCE 100

//----------- ESC's -----------
#define MIN_MOTOR_PULSE_WIDTH 1000
#define MAX_MOTOR_PULSE_WIDTH 2000

//----------- TIMEOUTS -----------
#define IMU_COMMUNICATION_TIMEOUT_IN_MILLISECONDS 100
#define RECEIVER_COMMUNICATION_TIMEOUT_IN_MILLISECONDS 500

//----------- LIMITS -----------
#define THROTTLE_START_POINT 10  // between 0-180
#define THROTTLE_LIMIT_POINT 180 // between 0-180
#define QUADCOPTER_MAX_TILT_ANGLE 10.00 // roll, pitch tilt angle limit in degrees
#define QUADCOPTER_MAX_YAW_ANGLE_CHANGE_PER_SECOND 45.00

#endif
