#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

Delay::Delay(int duration) {
  this->startTime = 0;
  this->duration = duration;
  this->priority = 1;
}

bool Delay::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void Delay::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  startTime = pros::millis();
}

void Delay::execute() {
  //printf("Claw control running\n");
  printf("Time at: %d\n", pros::millis() - startTime);
}

bool Delay::isFinished() {
  return pros::millis() - startTime >= duration;
}

void Delay::end() {
  // Code that runs when isFinished() returns true.
  printf("Finished delay\n");
}

void Delay::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
}
