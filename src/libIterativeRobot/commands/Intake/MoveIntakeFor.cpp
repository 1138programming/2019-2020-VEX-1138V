#include "libIterativeRobot/commands/MoveIntakeFor.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

//* Moves the Intake based off of time

MoveIntakeFor::MoveIntakeFor(unsigned int duration, int speed) {
  this->duration = duration;
  this->speed = speed;

  requires(Robot::intake);
  this->priority = 1;
}

bool MoveIntakeFor::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveIntakeFor::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  printf("Initializing intake\n");
  startTime = pros::millis();
}

void MoveIntakeFor::execute() {
    printf("Moving intake\n");
    Robot::intake->move(speed);
}

bool MoveIntakeFor::isFinished() {
  return pros::millis() > (startTime + duration);
}

void MoveIntakeFor::end() {
  // Code that runs when isFinished() returns true.
  printf("Intake Stopped\n");
  Robot::intake->move(0);
}

void MoveIntakeFor::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
  Robot::intake->move(0);
}

void MoveIntakeFor::blocked() {

}
