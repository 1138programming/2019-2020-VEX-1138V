#include "libIterativeRobot/commands/MoveAnglerTo.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

MoveAnglerTo::MoveAnglerTo(int target = 0) {
  requires(Robot::angler);
  this->priority = 1;
  this->target = target;
}

bool MoveAnglerTo::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveAnglerTo::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::angler->enablePID();
  Robot::angler->setSetpoint(target);
}

void MoveAnglerTo::execute() {
  //printf("Moving angler to: %d\n", target);
}

bool MoveAnglerTo::isFinished() {
  return Robot::angler->atSetpoint();
}

void MoveAnglerTo::end() {
  // Code that runs when isFinished() returns true.
  //Robot::angler->lock();
}

void MoveAnglerTo::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}
