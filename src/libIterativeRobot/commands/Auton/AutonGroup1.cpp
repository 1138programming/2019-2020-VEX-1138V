#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/commands/DriveForTime.h"
#include "libIterativeRobot/commands/MoveLiftFor.h"
#include "libIterativeRobot/commands/MoveIntakeFor.h"

//* Put the default auton here.


AutonGroup1::AutonGroup1() { 
  //* Humzah: Where it say 100, that is the time, MAKE SURE TO HAVE A 60%+ CHARGED BATTERY AS MUCH AS POSSIBLE
  //add parallel only one at a time, add sequential only while most recent parallel
  //left speed, right speed, time
  //Compile: prosv5 make WHENEVER YOU CHANGE THE CODE
  // Upload: prosv5 u --slot [slot as an int] --name "[name as a string]"
  // prosv5 u --slot 1 --name "1 cube auton"

  addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed/2));
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed/2, KMaxMotorSpeed/2, 1000));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed, -KMaxMotorSpeed, 300));

  //IMPORTANT NOTE: Lines a-b and c-d are the exact same, so just tune them to be the same ok 
  //IMPORTANT NOTE: ADD DELAYS AS NEEDED 

  /* addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed/2)); //start by lifting up
  addSequentialCommand(new MoveIntakeFor(300, KMaxMotorSpeed)); //grab cube 
  addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed)); //lift up 
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 300)); //drive forward to next cube, may not be necessary
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)) //lower cube onto next cube LINE A 
  addSequentialCommand(new MoveIntakeFor(300, -KMaxMotorSpeed)); //let go of cube
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)); //lower lift down
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 300); //may need to drive forward a little
  addSequentialCommand(new MoveIntakeFor(300, KMaxMotorSpeed)); //grab both cubes 
  addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed)); //lift both cubes up //LINE B 
  addSequentialCommand(new DriveForTime(300, KMaxMotorSpeed, -KMaxMotorSpeed)); //turn 90 degrees
  addSequentialCommand(new DriveForTime(300, KMaxMotorSpeed, KMaxMotorSpeed)); //drive forward to next cube 
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)) //lower cube onto next cube //LINE C 
  addSequentialCommand(new MoveIntakeFor(300, -KMaxMotorSpeed)); //let go of cube
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)); //lower lift down
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed, KMaxMotorSpeed, 300); //may need to drive forward a little
  addSequentialCommand(new MoveIntakeFor(300, KMaxMotorSpeed)); //grab both cubes 
  addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed)); //lift both cubes up  //LINE D 
  addSequentialCommand(new DriveForTime(300, KMaxMotorSpeed, KMaxMotorSpeed)); //drive forward into the zone 
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)); //lower the lift
  addSequentialCommand(new MoveIntakeFor(300, -KMaxMotorSpeed)); //release second cube 
  addSequentialCommand(new DriveForTime(300, -KMaxMotorSpeed, -KMaxMotorSpeed)); //pull back, auton is done, win wurlds 
  */
}
