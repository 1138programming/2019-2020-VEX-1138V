#ifndef _SUBSYSTEMS_SUBSYSTEM_H_
#define _SUBSYSTEMS_SUBSYSTEM_H_

#include "main.h"

namespace libIterativeRobot {

class Command;

/**
 * The Subsystem class is for encapsulating groups of motors and other objects such as PIDControllers that interact
 * physically on the robot.
 *
 * Commands require subsystems, and only one Command which requires a specific subsystem can run at a time. If another
 * Command that requires the same subsystem is added to the EventScheduler, it will either interrupt the first Command
 * or fail to run.
 *
 * Subsystems can have default Commands which run automatically if no other Commands require it
 */

class Subsystem {
  private:
    /**
     * @brief The Command to be used as a default Command.
     */
    Command* defaultCommand = NULL;
  protected:
    /**
      * @brief Sets the default Command for the Subsystem
      * @param aCommand The new default Command
      */
    void setDefaultCommand(Command* aCommand);

    /**
      * @brief Get the Subsystem's default Command.
      * @return The default Command
      */
    Command* getDefaultCommand();

    /**
     * @brief Allow the EventScheduler access to the Subsystems' getDefaultCommand() method
     */
    friend class EventScheduler;
  public:
    /**
     * @brief The number of Subsystems created
     */
    static size_t instances;

    /**
      * @brief Runs the default Command
      */
    virtual void initDefaultCommand() = 0;

    /**
     * @brief Creates a Subsystem
     * @return A Subsystem
     */
    Subsystem();
};

};

#endif // _SUBSYSTEMS_SUBSYSTEM_H_
