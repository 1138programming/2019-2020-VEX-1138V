#include "libIterativeRobot/commands/StopAngler.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

StopAngler::StopAngler() {
  //requires(Robot::angler);
  //this->priority = DefaultCommandPriority; // Lowest priority
}

bool StopAngler::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void StopAngler::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::angler->move(0);
  //Robot::angler->lock();
  //Robot::angler->enablePID();
}

void StopAngler::execute() {
  Robot::angler->move(0);
  //printf("Stopping angler\n");
}

bool StopAngler::isFinished() {
  return false;
}

void StopAngler::end() {
  // Code that runs when isFinished() returns true.
}

void StopAngler::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}
