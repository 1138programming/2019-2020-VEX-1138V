#ifndef _COMMANDS_DRIVEFORTIME_H_
#define _COMMANDS_DRIVEFORTIME_H_

#include "libIterativeRobot/commands/Command.h"

class DriveForTime: public libIterativeRobot::Command {
  public:
    bool canRun();
    void initialize();
    void execute();
    bool isFinished();
    void end();
    void interrupted();
    void blocked();
    DriveForTime(int leftSideSpeed, int rightSideSpeed, unsigned int duration);
  private:
    int leftSideSpeed;
    int rightSideSpeed;
    unsigned int duration;
    unsigned int startTime;
};

#endif // _COMMANDS_DRIVEFORTIME_H_
