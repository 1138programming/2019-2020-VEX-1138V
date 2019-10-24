#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/DriveForTime.h"
#include "libIterativeRobot/commands/Delay.h"

AutonGroup1::AutonGroup1() {
  /*addSequentialCommand(new Delay(1000));
  addParallelCommand(new AutonGroup2());
  addSequentialCommand(new Delay(1000));*/
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 375));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 500));
}
