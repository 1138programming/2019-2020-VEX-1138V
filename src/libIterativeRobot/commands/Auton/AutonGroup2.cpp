#include "libIterativeRobot/commands/AutonGroup2.h"
#include "libIterativeRobot/commands/Delay.h"
#include "libIterativeRobot/commands/BaseLinearMovement.h"
#include "libIterativeRobot/commands/DriveForTime.h"
#include "libIterativeRobot/commands/MoveLiftFor.h"
#include "libIterativeRobot/commands/MoveIntakeFor.h"

//* Secondary auton


AutonGroup2::AutonGroup2() {
    addSequentialCommand(new MoveLiftFor(400, KMaxMotorSpeed/3)); //start by lifting up
  addSequentialCommand(new MoveIntakeFor(1000, -200)); //grab cube
  addSequentialCommand(new MoveLiftFor(1200, KMaxMotorSpeed/2)); //lift up
  addSequentialCommand(new BaseLinearMovement(300, 225, 2, 0.005)); //drive forward to next cube, may not be necessary
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed/3)); //! lower cube onto next cube LINE A
  addSequentialCommand(new MoveIntakeFor(300, +KMaxMotorSpeed)); //let go of cube
  addSequentialCommand(new MoveLiftFor(750, -KMaxMotorSpeed/2)); //lower lift down
  addSequentialCommand(new BaseLinearMovement(470, 420, 2, 0.002)); //may need to drive forward a little
  addSequentialCommand(new MoveIntakeFor(600, -KMaxMotorSpeed)); //grab both cubes
  addSequentialCommand(new MoveLiftFor(800, KMaxMotorSpeed/3x)); //! lift both cubes up //LINE B
  addParallelCommand(new MoveIntakeFor(800, -KMaxMotorSpeed/2), true); 
  addSequentialCommand(new DriveForTime(-KMaxMotorSpeed/3, KMaxMotorSpeed/3, 1400)); //to turn 
  addSequentialCommand(new DriveForTime(KMaxMotorSpeed/2, KMaxMotorSpeed/2, 2000)); //drive forward into the zone
  addSequentialCommand(new MoveLiftFor(300, -KMaxMotorSpeed)); //lower the lift
  addSequentialCommand(new MoveIntakeFor(300, +KMaxMotorSpeed)); //release second cube
  addSequentialCommand(new BaseLinearMovement(-5000, -5000, 3, 0.01)); //pull back, auton is done, win wurlds
}
