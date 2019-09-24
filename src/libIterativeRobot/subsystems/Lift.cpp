#include "main.h"
#include "libIterativeRobot/commands/StopLift.h"

Lift::Lift() {
  // Get lift motors
  leftLiftMotor = Motor::getMotor(leftLiftPort, liftMotorGearset);
  rightLiftMotor = Motor::getMotor(rightLiftPort, liftMotorGearset);

  leftLiftMotor->reverse();
  leftLiftController = new PIDController(leftLiftMotor, 0.32, 0, 0.05);
  rightLiftController = new PIDController(rightLiftMotor, 0.32, 0, 0.05);
}

void Lift::initDefaultCommand() {
  setDefaultCommand(new StopLift());
}

/**
 * Move the lift
 * @param left - speed of the left side
 * @param right - speed of the right side
 */
pros::ADIDigitalIn bumper ('a');
void Lift::move(int speed) {
  //printf("Lift speed is %d\n", speed);
  if (bumper.get_value())
  {
    leftLiftMotor->setSpeed(KMaxMotorSpeed);
    rightLiftMotor->setSpeed(KMaxMotorSpeed);
    printf("Motor speed reversed.");
  }
  else
  {
    leftLiftMotor->setSpeed(speed);
    rightLiftMotor->setSpeed(speed);
  }
}

void Lift::setSetpoint(int setpoint) {
  leftLiftMotor->setSpeed(setpoint);
  rightLiftController->setSetpoint(setpoint);
}

bool Lift::atSetpoint() {
  return leftLiftController->atSetpoint();
  return rightLiftController->atSetpoint();
}

void Lift::loop() {
  leftLiftController->loop();
  rightLiftController->loop();
}

void Lift::lock() {
  leftLiftController->lock();
  rightLiftController->lock();
}

void Lift::disablePID() {
  leftLiftController->disable();
  rightLiftController->disable();
}

void Lift::enablePID() {
  leftLiftController->enable();
  rightLiftController->enable();
}
