#include "main.h"
#include "libIterativeRobot/commands/StopAngler.h"

Angler::Angler() {
  // Get angler motors
  anglerMotor = Motor::getMotor(anglerPort, anglerMotorGearset);

  anglerController = new PIDController(anglerMotor, 0.32, 0, 0.05);
}

void Angler::initDefaultCommand() {
  setDefaultCommand(new StopAngler());
}

/**
 * Move the angler
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
pros::ADIDigitalIn bumper ('a');
void Angler::move(int speed) {
  //printf("Angler speed is %d\n", speed);
  if (bumper.get_value())
  {
    anglerMotor->setSpeed(KMaxMotorSpeed);
    printf("Motor speed reversed.");
  }
  else
  {
    anglerMotor->setSpeed(speed);
  }
}

void Angler::setSetpoint(int setpoint) {
  anglerController->setSetpoint(setpoint);
}

bool Angler::atSetpoint() {
  return anglerController->atSetpoint();
}

void Angler::loop() {
  anglerController->loop();
}

void Angler::lock() {
  anglerController->lock();
}

void Angler::disablePID() {
  anglerController->disable();
}

void Angler::enablePID() {
  anglerController->enable();
}
