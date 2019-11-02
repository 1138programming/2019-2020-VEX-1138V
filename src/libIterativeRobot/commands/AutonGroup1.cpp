#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/commands/DriveForTime.h"
#include "libIterativeRobot/commands/MoveLiftFor.h"
#include "libIterativeRobot/commands/MoveIntakeFor.h"

AutonGroup1::AutonGroup1() { //* Humzah: Where it say 100, that is the time, MAKE SURE TO HAVE A 60%+ CHARGED BATTERY AS MUCH AS POSSIBLE
 //add parallel only one at a time, add sequential only while most recent parallel
  //left speed, right speed, time
  //Compile: prosv5 make WHENEVER YOU CHANGE THE CODE
  // Upload: prosv5 u --slot [slot as an int] --name "[name as a string]"
  // prosv5 u --slot 1 --name "1 cube auton"
  //addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 100));
  //addParallelCommand(new MoveLiftFor(100, KMaxMotorSpeed));
  //addParallelCommand(new MoveIntakeFor(100, KMaxMotorSpeed));

  addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed/2));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed/2, KMaxMotorSpeed/2, 1000));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed/2, -KMaxMotorSpeed/2, 300));
}
