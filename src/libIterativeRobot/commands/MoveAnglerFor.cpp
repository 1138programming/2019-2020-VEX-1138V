#include "libIterativeRobot/commands/MoveAnglerFor.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

MoveAnglerFor::MoveAnglerFor(unsigned int duration, int speed) {
  this->duration = duration;
  this->speed = speed;

  requires(Robot::angler);
  this->priority = 1;
}

bool MoveAnglerFor::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveAnglerFor::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  printf("Initiating move angler\n");
  pros::delay(1000);
  startTime = pros::millis();
}

void MoveAnglerFor::execute() {
    Robot::angler->move(speed);
}

bool MoveAnglerFor::isFinished() {
  return pros::millis() > (startTime + duration);
}

void MoveAnglerFor::end() {
  // Code that runs when isFinished() returns true.
  Robot::angler->move(0);
}

void MoveAnglerFor::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
  Robot::angler->move(0);
}
