#include "libIterativeRobot/commands/MoveLiftTo.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

//* Hopeful movement of lift based off PID.

MoveLiftTo::MoveLiftTo(int target = 0) {
  requires(Robot::lift);
  this->priority = 1;
  this->target = target;
}

bool MoveLiftTo::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveLiftTo::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::lift->enablePID();
  Robot::lift->setSetpoint(target);
}

void MoveLiftTo::execute() {
  //printf("Moving lift to: %d\n", target);
}

bool MoveLiftTo::isFinished() {
  return Robot::lift->atSetpoint();
}

void MoveLiftTo::end() {
  // Code that runs when isFinished() returns true.
  //Robot::lift->lock();
}

void MoveLiftTo::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void MoveLiftTo::blocked() {

}
