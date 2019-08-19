#include "main.h"
#include "libIterativeRobot/commands/StopIntake.h"

Intake::Intake() {
  // Get intake motors
  leftIntakeMotor = Motor::getMotor(leftIntakeMotorPort, intakeMotorGearset);
  rightIntakeMotor = Motor::getMotor(rightIntakeMotorPort, intakeMotorGearset);

  rightIntakeMotor->reverse();
}

void Intake::initDefaultCommand() {
  setDefaultCommand(new StopIntake());
}

/**
 * Move the intake
 * @param speed - speed of the speed side
 * @param right - speed of the right side
 */

void Intake::move(int speed) {
  leftIntakeMotor->setSpeed(speed);
  rightIntakeMotor->setSpeed(speed);
  printf("Motor speed set to %d\n", speed);
}
