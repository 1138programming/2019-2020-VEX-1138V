#include "main.h"
#include "libIterativeRobot/commands/StopBase.h"

Base::Base() {
  // Set up motors
  frontLeftMotor = Motor::getMotor(frontLeftBasePort, baseMotorGearset);
  frontRightMotor = Motor::getMotor(frontRightBasePort, baseMotorGearset);
  backLeftMotor = Motor::getMotor(backLeftBasePort, baseMotorGearset);
  backRightMotor = Motor::getMotor(backRightBasePort, baseMotorGearset);

  backLeftMotor->reverse();
  frontLeftMotor->reverse();
}

void Base::initDefaultCommand() {
  // Setup up a default command here
  setDefaultCommand(new StopBase());
}

/**
 * Move the base
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
void Base::moveAtSpeed(int leftSpeed, int rightSpeed) {
  frontLeftMotor->setSpeed(leftSpeed);
  frontRightMotor->setSpeed(rightSpeed);
  backLeftMotor->setSpeed(leftSpeed);
  backRightMotor->setSpeed(rightSpeed);
}
