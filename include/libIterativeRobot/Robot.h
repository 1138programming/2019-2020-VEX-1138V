#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "main.h"
#include "RobotBase.h"
#include "subsystems/Base.h"
#include "commands/CommandGroup.h"

class Robot : public libIterativeRobot::RobotBase {
  private:
    static Robot* instance;
    Robot();
  protected:
    void robotInit();
    void autonInit();
    void autonPeriodic();
    void teleopInit();
    void teleopPeriodic();
    void disabledInit();
    void disabledPeriodic();
  public:
    static Robot* getInstance();

    // Pointers to every subsystem on the robot:
    static Base* base;
    static Lift*  lift;
    static Intake* intake;

    static AutonChooser* autonChooser;

    // Pointers to controllers
    static pros::Controller* mainController;
    static pros::Controller* partnerController;
};


#endif // _ROBOT_H_
