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
  //addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 100));
  //addParallelCommand(new MoveLiftFor(100, KMaxMotorSpeed));
  //addParallelCommand(new MoveIntakeFor(100, KMaxMotorSpeed));

  /* addParallelCommand(new MoveLiftFor(100, KMaxMotorSpeed)); //lift up tiny bit allow intake to open
  addParallelCommand(new MoveIntakeFor(100, KMaxMotorSpeed)); //move into in
  addParallelCommand(new MoveLiftFor(100, -KMaxMotorSpeed)); //back down
  addParallelCommand(new MoveIntakeFor(100, KMaxMotorSpeed)); //grab cube
  addParallelCommand(new MoveLiftFor(100, KMaxMotorSpeed)) //lift cube up, so it doesn't drag and also to get next
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 100)); //drive forward to next cube
  addParallelCommand(new MoveIntakeFor(100, -KMaxMotorSpeed)); //release cube ontop of other cube
  addParallelCommand(new MoveLiftFor(100, -KMaxMotorSpeed)); //drop lift
  addParallelCommand(new MoveIntakeFor(100, KMaxMotorSpeed)); //grab both cubes
  addParallelCommand(new MoveLiftFor(100, KMaxMotorSpeed)); //lift up both cubes
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 100)); //drive back until hit the wall
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed, KMaxMotorSpeed, 100)); // turn 90 deg left toward the zone
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 100)); //drive to zone
  addParallelCommand(new MoveLiftFor(100, -KMaxMotorSpeed)); //drop into zone
  addParallelCommand(new MoveIntakeFor(100, -KMaxMotorSpeed)); //release in zone
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 100)); //pull back so we aren't touching. auton end */

  addSequentialCommand(new MoveLiftFor(500, KMaxMotorSpeed));
  addParallelCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 500));
  addParallelCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 200));
}
