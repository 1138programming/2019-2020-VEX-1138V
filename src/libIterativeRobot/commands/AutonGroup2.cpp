#include "libIterativeRobot/commands/AutonGroup2.h"
#include "libIterativeRobot/commands/Delay.h"

AutonGroup2::AutonGroup2() {
  addSequentialCommand(new Delay(5000));
}
