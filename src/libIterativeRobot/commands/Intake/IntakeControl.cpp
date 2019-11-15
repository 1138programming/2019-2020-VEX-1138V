#include "libIterativeRobot/commands/IntakeControl.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

//* Controls the Intake without duration or distance

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
  printf("Intake Initialized\n");
}

void IntakeControl::execute() {
  printf("Intake execute\n");
}

bool IntakeControl::isFinished() {
  return false;
}

void IntakeControl::end() {
  // Code that runs when isFinished() returns true.
  printf("Intake Stopped\n");
}

void IntakeControl::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}

void IntakeControl::blocked() {

}
