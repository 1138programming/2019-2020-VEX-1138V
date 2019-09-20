#ifndef _COMMANDS_STOPCLAW_H_
#define _COMMANDS_STOPCLAW_H_

#include "libIterativeRobot/commands/Command.h"

class StopIntake: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    StopIntake();
  private:
};

#endif // _COMMANDS_STOPCLAW_H_
