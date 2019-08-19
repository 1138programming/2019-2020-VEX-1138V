#ifndef _COMMANDS_MOVEARMTO_H_
#define _COMMANDS_MOVEARMTO_H_

#include "libIterativeRobot/commands/Command.h"

class MoveAnglerTo: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    MoveAnglerTo(int target);
  private:
    int target = 0;
};

#endif // _COMMANDS_MOVEARMTO_H_
