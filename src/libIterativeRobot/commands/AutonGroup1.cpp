#include "libIterativeRobot/commands/AutonGroup2.h"
#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/commands/DriveForTime.h"
#include "libIterativeRobot/commands/MoveLiftFor.h"
#include "libIterativeRobot/commands/MoveIntakeFor.h"

AutonGroup2::AutonGroup2() { //* Humzah: Where it say 100, that is the time, MAKE SURE TO HAVE A 60%+ CHARGED BATTERY AS MUCH AS POSSIBLE
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 100));
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, -KMaxMotorSpeed, 100));
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 100));
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 100));
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed, KMaxMotorSpeed, 100));
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 100));
  addParallelCommand(new MoveLiftFor(100, KMaxMotorSpeed));
  addParallelCommand(new MoveIntakeFor(100, KMaxMotorSpeed));
  addParallelCommand(new MoveLiftFor(100, KMaxMotorSpeed));
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 100));
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, -KMaxMotorSpeed, 100));
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 100));
  addParallelCommand(new MoveLiftFor(100, -KMaxMotorSpeed));
  addParallelCommand(new MoveIntakeFor(100, -KMaxMotorSpeed));
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 100));
}