#ifndef _COMMANDS_DELAY_H_
#define _COMMANDS_DELAY_H_

#include "libIterativeRobot/commands/Command.h"

class Delay: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    Delay(int duration);
  private:
    int startTime;
    int duration;
};

#endif // _COMMANDS_DELAY_H_
