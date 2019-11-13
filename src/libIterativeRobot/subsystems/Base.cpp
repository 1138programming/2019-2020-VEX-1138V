#include "main.h"
#include "libIterativeRobot/commands/StopBase.h"

const double Base::kDefaultMaxAccel = 0.01;
const double Base::kDefaultMaxVel = 3.0;

Base::Base() {
  // Set up motors
  frontLeftMotor = Motor::getMotor(frontLeftBasePort, baseMotorGearset);
  frontRightMotor = Motor::getMotor(frontRightBasePort, baseMotorGearset);
  backLeftMotor = Motor::getMotor(backLeftBasePort, baseMotorGearset);
  backRightMotor = Motor::getMotor(backRightBasePort, baseMotorGearset);
  frontRightMotor->reverse();
  backRightMotor->reverse();

  frontLeftMotor->addFollower(backLeftMotor);
  frontRightMotor->addFollower(backRightMotor);

  leftProfiler = new LinearProfiler(frontLeftMotor, 2, 0.017, 0.7, 0, 0);
  rightProfiler = new LinearProfiler(frontRightMotor, 2, 0.017, 0.7, 0, 0);

  leftProfiler->setThreshold(15);
  rightProfiler->setThreshold(15);
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

void Base::setLinearTarget(int leftTarget, int rightTarget) {
  leftProfiler->setTarget(leftTarget);
  rightProfiler->setTarget(rightTarget);
}

void Base::setLinearTargetRelative(int leftTarget, int rightTarget) {
  leftProfiler->setTargetRelative(leftTarget);
  rightProfiler->setTargetRelative(rightTarget);
}

void Base::initLinearMovement() {
  leftProfiler->init();
  rightProfiler->init();
}

void Base::updateLinearMovement() {
  leftProfiler->update();
  rightProfiler->update();
}

bool Base::atLinearTarget() {
  return leftProfiler->atTarget() && rightProfiler->atTarget();
}

void Base::stopLinearMovement() {
  leftProfiler->stop();
  rightProfiler->stop();
}

void Base::setMaxVel(double maxVel) {
  //printf("Setting maxVel to %f\n", maxVel);
  leftProfiler->setMaxVel(maxVel);
  rightProfiler->setMaxVel(maxVel);
}

void Base::setMaxAccel(double maxAccel) {
  //printf("Setting maxAccel to %f\n", maxAccel);
  leftProfiler->setMaxAccel(maxAccel);
  rightProfiler->setMaxAccel(maxAccel);
}

LinearProfiler* Base::getLeftProfiler() {
  return leftProfiler;
}

LinearProfiler* Base::getRightProfiler() {
  return rightProfiler;
}
