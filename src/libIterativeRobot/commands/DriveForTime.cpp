#include "libIterativeRobot/commands/DriveForTime.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

DriveForTime::DriveForTime(int leftSideSpeed, int rightSideSpeed, unsigned int duration) {
  this->leftSideSpeed = leftSideSpeed;
  this->rightSideSpeed = rightSideSpeed;
  this->duration = duration;
  
  requires(Robot::base);
  this->priority = 2;
}

bool DriveForTime::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void DriveForTime::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  startTime = pros::millis();
}

void DriveForTime::execute() {
  Robot::base->moveAtSpeed(leftSideSpeed, rightSideSpeed);
}

bool DriveForTime::isFinished() {
  return pros::millis() > (startTime + duration);
}

void DriveForTime::end() {
  // Code that runs when isFinished() returns true.
  Robot::base->moveAtSpeed(0, 0);
}

void DriveForTime::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
  Robot::base->moveAtSpeed(0, 0);
}

void DriveForTime::blocked() {
  
}