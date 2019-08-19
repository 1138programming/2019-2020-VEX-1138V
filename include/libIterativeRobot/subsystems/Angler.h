#ifndef _SUBSYSTEMS_ARM_H_
#define _SUBSYSTEMS_ARM_H_

#include "./Subsystem.h"
#include "api.h"

class Angler : public libIterativeRobot::Subsystem {
  private:
    // Angler motors
    Motor* anglerMotor;

    PIDController* anglerController;

  public:
    void initDefaultCommand();
    void move(int speed);
    void setSetpoint(int setpoint);
    bool atSetpoint();
    void loop();
    void lock();
    void disablePID();
    void enablePID();
    Angler();
};

#endif // _SUBSYSTEMS_ARM_H_
