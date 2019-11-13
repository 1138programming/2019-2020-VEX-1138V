#ifndef _SUBSYSTEMS_BASE_H_
#define _SUBSYSTEMS_BASE_H_

#include "./Subsystem.h"
#include "abstractBaseClasses/LinearProfiler.h"
#include "api.h"

class Base : public libIterativeRobot::Subsystem {
  private:
    // Base motors
    Motor* frontLeftMotor;
    Motor* frontRightMotor;
    Motor* backLeftMotor;
    Motor* backRightMotor;

    LinearProfiler* leftProfiler;
    LinearProfiler* rightProfiler;
  public:
    static const double kDefaultMaxAccel;
    static const double kDefaultMaxVel;

    void initDefaultCommand();
    void moveAtSpeed(int leftSpeed, int rightSpeed);
    void setLinearTarget(int leftTarget, int rightTarget);
    void setLinearTargetRelative(int leftTarget, int rightTarget);
    void initLinearMovement();
    void updateLinearMovement();
    bool atLinearTarget();
    void stopLinearMovement();
    void setMaxVel(double maxVel);
    void setMaxAccel(double maxAccel);
    LinearProfiler* getLeftProfiler();
    LinearProfiler* getRightProfiler();
    Base();
};

#endif // _SUBSYSTEMS_BASE_H_
