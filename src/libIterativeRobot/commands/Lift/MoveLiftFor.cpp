#include "libIterativeRobot/commands/MoveLiftFor.h"
#include "libIterativeRobot/Robot.h"
#include "Constants.h"

//* Moves Lift for duration

MoveLiftFor::MoveLiftFor(unsigned int duration, int speed) {
  this->duration = duration;
  this->speed = speed;

  requires(Robot::lift);
  this->priority = 1;
}

bool MoveLiftFor::canRun() {
  return true; // This is the default value anyways, so this method can be removed
}

void MoveLiftFor::initialize() {
  // Perform any initialization steps for this command here, not in the
  // constructor
  printf("Initiating move lift\n");
  startTime = pros::millis();
}

void MoveLiftFor::execute() {
    printf("Moving lift, time is %d\n", pros::millis() - startTime);
    Robot::lift->move(speed);
}

bool MoveLiftFor::isFinished() {
  return pros::millis() > (startTime + duration);
}

void MoveLiftFor::end() {
  // Code that runs when isFinished() returns true.
  Robot::lift->move(0);
}

void MoveLiftFor::interrupted() {
  // Code that runs when this command is interrupted by another one
  // with a higher priority.
  Robot::lift->move(0);
}

void MoveLiftFor::blocked() {

}
