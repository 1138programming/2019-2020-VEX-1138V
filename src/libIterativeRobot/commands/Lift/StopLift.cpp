#include "libIterativeRobot/commands/StopLift.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

//* Stop lift

StopLift::StopLift() {
  //requires(Robot::lift);
  //this->priority = DefaultCommandPriority; // Lowest priority
}

bool StopLift::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void StopLift::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  Robot::lift->move(0);
  //Robot::lift->lock();
  //Robot::lift->enablePID();
}

void StopLift::execute() {
  Robot::lift->move(0);
  //printf("Stopping lift\n");
}

bool StopLift::isFinished() {
  return false;
}

void StopLift::end() {
  // Code that runs when isFinished() returns true.
}

void StopLift::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void StopLift::blocked() {

}
