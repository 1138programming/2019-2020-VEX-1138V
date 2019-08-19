#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/AutonGroup2.h"
#include "libIterativeRobot/commands/Delay.h"

AutonGroup1::AutonGroup1() {
  addSequentialCommand(new Delay(1000));
  addParallelCommand(new AutonGroup2());
  addSequentialCommand(new Delay(1000));
}
