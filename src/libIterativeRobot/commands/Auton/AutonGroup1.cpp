#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/commands/BaseLinearMovement.h"
#include "libIterativeRobot/commands/MoveLiftFor.h"
#include "libIterativeRobot/commands/MoveIntakeFor.h"

//* Put the default auton here.


AutonGroup1::AutonGroup1() { 
  //* Humzah: Where it say 100, that is the time, MAKE SURE TO HAVE A 60%+ CHARGED BATTERY AS MUCH AS POSSIBLE
  //add parallel only one at a time, add sequential only while most recent parallel
  //left speed, right speed, time
  //Compile: "prosv5 make" WHENEVER YOU CHANGE THE CODE
  // Upload: "prosv5 u --slot [slot as an int] --name '[name as a string]'"
  // prosv5 u --slot 1 --name "1 cube auton"

  /*addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed/2));
  addSequentialCommand(new BaseLinearMovement(5000, 5000, 3, 0.01));
  addSequentialCommand(new Delay(500));
  addSequentialCommand(new BaseLinearMovement-(5000, -5000, 3, 0.01));*/

  //*IMPORTANT NOTE: Lines a-b and c-d are the exact same, so just tune them to be the same ok 
  //*IMPORTANT NOTE: ADD DELAYS AS NEEDED 

  addSequentialCommand(new MoveLiftFor(200, KMaxMotorSpeed/3)); //start by lifting up
  addSequentialCommand(new MoveIntakeFor(1000, -200)); //grab cube 
  addSequentialCommand(new MoveLiftFor(2000, KMaxMotorSpeed/3)); //lift up 
  addSequentialCommand(new BaseLinearMovement(400, 400, 2, 0.005)); //drive forward to next cube, may not be necessary
  addSequentialCommand(new MoveLiftFor(150, -KMaxMotorSpeed)); //! lower cube onto next cube LINE A 
  addSequentialCommand(new MoveIntakeFor(300, +KMaxMotorSpeed)); //let go of cube
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)); //lower lift down
  addSequentialCommand(new BaseLinearMovement(470, 470, 2, 0.003)); //may need to drive forward a little
  addSequentialCommand(new MoveIntakeFor(600, -KMaxMotorSpeed)); //grab both cubes 
  addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed)); //! lift both cubes up //LINE B 
  addSequentialCommand(new BaseLinearMovement(3000, -3000, 2, 0.003)); //turn 90 degrees
  addSequentialCommand(new BaseLinearMovement(5000, 5000, 3, 0.003)); //drive forward to next cube 
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)); //! lower cube onto next cube //LINE C 
  addSequentialCommand(new MoveIntakeFor(300, +KMaxMotorSpeed)); //let go of cube
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)); //lower lift down
  addSequentialCommand(new BaseLinearMovement(5000, 5000, 3, 0.01)); //may need to drive forward a little
  addSequentialCommand(new MoveIntakeFor(300, -KMaxMotorSpeed)); //grab both cubes 
  addSequentialCommand(new MoveLiftFor(300, KMaxMotorSpeed)); //! lift both cubes up  //LINE D 
  addSequentialCommand(new BaseLinearMovement(5000, 5000, 3, 0.01)); //drive forward into the zone 
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)); //lower the lift
  addSequentialCommand(new MoveIntakeFor(300, +KMaxMotorSpeed)); //release second cube 
  addSequentialCommand(new BaseLinearMovement(5000, 5000, 3, 0.01)); //pull back, auton is done, win wurlds 
}
