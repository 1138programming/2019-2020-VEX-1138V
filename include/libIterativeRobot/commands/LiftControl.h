#ifndef _COMMANDS_LIFTCONTROL_H_
#define _COMMANDS_LIFTCONTROL_H_

#include "libIterativeRobot/commands/Command.h"

class LiftControl: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    LiftControl(bool Open);
  private:
    bool Up;
};

#endif // _COMMANDS_CLAWCONTROL_H_
