#include "libIterativeRobot/commands/DriveWithJoy.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

//* Moves the base using the joysticks


DriveWithJoy::DriveWithJoy() {
  requires(Robot::base);
  this->priority = 2;
}

bool DriveWithJoy::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void DriveWithJoy::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  rightSideSpeed = Robot::mainController->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - Robot::mainController->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  leftSideSpeed = Robot::mainController->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + Robot::mainController->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
}

void DriveWithJoy::execute() {
  Robot::base->moveAtSpeed(leftSideSpeed, rightSideSpeed);
}

bool DriveWithJoy::isFinished() {
  return true;
}

void DriveWithJoy::end() {
  // Code that runs when isFinished() returns true.
}

void DriveWithJoy::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void DriveWithJoy::blocked() {
  
}