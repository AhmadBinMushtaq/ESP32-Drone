#include <Arduino.h>
#include "Functions.h"
#include "Constants.h"
#include "Structs.h"
#include "ESC.h"

ESC frontLeftMotor(FRONT_LEFT_MOTOR_PIN, MIN_MOTOR_PULSE_WIDTH, MAX_MOTOR_PULSE_WIDTH);
ESC frontRightMotor(FRONT_RIGHT_MOTOR_PIN, MIN_MOTOR_PULSE_WIDTH, MAX_MOTOR_PULSE_WIDTH);
ESC rearLeftMotor(REAR_LEFT_MOTOR_PIN, MIN_MOTOR_PULSE_WIDTH, MAX_MOTOR_PULSE_WIDTH);
ESC rearRightMotor(REAR_RIGHT_MOTOR_PIN, MIN_MOTOR_PULSE_WIDTH, MAX_MOTOR_PULSE_WIDTH);

void initializeMotors() {

  stopMotors();
}

void spinMotors(struct MotorPowers motorPowers) {
  frontLeftMotor.write(motorPowers.frontLeftMotorPower);
  frontRightMotor.write(motorPowers.frontRightMotorPower);
  rearLeftMotor.write(motorPowers.rearLeftMotorPower);
  rearRightMotor.write(motorPowers.rearRightMotorPower);
}

void stopMotors() {
  frontLeftMotor.write(0);
  frontRightMotor.write(0);
  rearLeftMotor.write(0);
  rearRightMotor.write(0);
}
