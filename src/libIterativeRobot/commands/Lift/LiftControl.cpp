#include "libIterativeRobot/commands/LiftControl.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

//* Controls the Lift without distance or duration

LiftControl::LiftControl(bool Up) {
  this->Up = Up;
  requires(Robot::lift);
  this->priority = 2;
}

bool LiftControl::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void LiftControl::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  // printf("Lift control initialized\n");
  Robot::lift->disablePID();
}

void LiftControl::execute() {
  //printf("Lift control running\n");
  if (this->Up)
    Robot::lift->move(KMaxMotorSpeed);
  else
    Robot::lift->move(-KMaxMotorSpeed);
}

bool LiftControl::isFinished() {
  return true;
}

void LiftControl::end() {
  // Code that runs when isFinished() returns true.
  //Robot::lift->lock();
}

void LiftControl::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void LiftControl::blocked() {

}
