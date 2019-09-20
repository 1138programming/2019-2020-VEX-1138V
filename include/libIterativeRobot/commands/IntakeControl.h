#ifndef _COMMANDS_CLAWCONTROL_H_
#define _COMMANDS_CLAWCONTROL_H_

#include "libIterativeRobot/commands/Command.h"

class IntakeControl: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    IntakeControl(bool Open);
  private:
    bool Open;
};

#endif // _COMMANDS_CLAWCONTROL_H_
