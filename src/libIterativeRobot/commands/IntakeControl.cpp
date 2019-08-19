#include "libIterativeRobot/commands/IntakeControl.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

IntakeControl::IntakeControl(bool Open) {
  this->Open = Open;
  requires(Robot::intake);
  this->priority = 2;
}

bool IntakeControl::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void IntakeControl::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  if (this->Open)
    Robot::intake->move(KMaxMotorSpeed);
  else
    Robot::intake->move(-KMaxMotorSpeed);
}

void IntakeControl::execute() {
}

bool IntakeControl::isFinished() {
  return false;
}

void IntakeControl::end() {
  // Code that runs when isFinished() returns true.
}

void IntakeControl::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}
