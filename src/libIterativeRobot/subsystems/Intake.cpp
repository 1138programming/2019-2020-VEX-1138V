#include "main.h"
#include "libIterativeRobot/commands/StopIntake.h"

Intake::Intake() {
  // Get intake motors
  intakeMotor = Motor::getMotor(intakeMotorPort, intakeMotorGearset);

  intakeMotor->reverse();
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
  intakeMotor->setSpeed(speed);
  printf("Motor speed set to %d\n", speed);
}
