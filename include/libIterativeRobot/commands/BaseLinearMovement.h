#ifndef _BASELINEARMOVEMENT_H_
#define _BASELINEARMOVEMENT_H_

#include "libIterativeRobot/commands/Command.h"

class BaseLinearMovement : public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    BaseLinearMovement(int leftTarget, int rightTarget);
    BaseLinearMovement(int leftTarget, int rightTarget, double maxVel, double maxAccel);
    BaseLinearMovement(int leftTarget, int rightTarget, bool absolute);
    BaseLinearMovement(int leftTarget, int rightTarget, double maxVel, double maxAccel, bool absolute);
  private:
    int leftTarget;
    int rightTarget;
    double maxVel;
    double maxAccel;
    bool absolute;
};

#endif //_BASELINEARMOVEMENT_H_
