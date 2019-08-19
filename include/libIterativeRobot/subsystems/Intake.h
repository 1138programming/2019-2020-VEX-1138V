#ifndef _SUBSYSTEMS_CLAW_H_
#define _SUBSYSTEMS_CLAW_H_

#include "./Subsystem.h"
#include "api.h"

class Intake : public libIterativeRobot::Subsystem {
  private:
    // Claw motors
    Motor* leftIntakeMotor;
    Motor* rightIntakeMotor;
    
  public:
    void initDefaultCommand();
    void move(int speed);
    Intake();
};

#endif // _SUBSYSTEMS_CLAW_H_
