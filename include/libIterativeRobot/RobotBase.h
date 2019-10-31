#ifndef _ROBOTBASE_H_
#define _ROBOTBASE_H_

#include "main.h"
#include "pros/rtos.hpp"

namespace libIterativeRobot {
  class RobotBase {
    private:
      /**
       * @brief Possible robot states are None, Auton, Teleop, and Disabled
       */
      enum class RobotState {
        None,
        Auton,
        Teleop,
        Disabled,
      };

      /**
       * @brief Stores the last state of the robot
       */
      RobotState lastState = RobotState::None;

      /**
       * @brief Main loop of the entire robot.
       *
       * Runs the function corresponding with the current state. For example, in autonomous code, doOneCycle runs autonInit and autonPeriodic.
       */
      void doOneCycle();

      /**
       * @brief
       */
      static void _privateRunRobot(void* param);
    protected:
      /**
        * @brief Runs when the robot starts up.
        */
      virtual void robotInit() = 0;

      /**
        * @brief Runs once each time the autonomous period begins.
        */
      virtual void autonInit() = 0;

      /**
        * @brief Runs in a loop during the autonomous period.
        */
      virtual void autonPeriodic() = 0;

      /**
        * @brief Runs once each time the teleoperated period begins.
        */
      virtual void teleopInit() = 0;

      /**
        * @brief Runs in a loop during the teleoperated period.
        */
      virtual void teleopPeriodic() = 0;

      /**
        * @brief Runs once each time the robot is disabled.
        */
      virtual void disabledInit() = 0;

      /**
        * @brief Runs in a loop while the robot is disabled.
        */
      virtual void disabledPeriodic() = 0;

      /**
       * @brief Starts the task that runs doOneCycle
       */
      void runRobot();

      RobotBase();
    public:
      /**
        * @brief Starts the robot
        *
        * Creates an instance of the Robot class and calls runRobot on it.
        * This should be called in the initialize function in initialize.cpp
        */
      static void initializeRobot();
  };
}
#endif // _ROBOTBASE_H_
