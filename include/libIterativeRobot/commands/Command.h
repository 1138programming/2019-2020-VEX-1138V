#ifndef _COMMANDS_COMMAND_H_
#define _COMMANDS_COMMAND_H_

#include "main.h"
#include "libIterativeRobot/subsystems/Subsystem.h"
#include <vector>
#include "libIterativeRobot/commands/Status.h"

namespace libIterativeRobot {

/**
 * @mainpage Refactored-Chainsaw documentation
 */

/**
 * The Command class is the base class for all commands.
 * Commands implement functionality for one or more subsystems,
 * and their execution and interactions are handled by the EventScheduler.
 * Commands are added to the EventScheduler
 * when their run() method is called, and the command starts if its canRun() method returns true.
 * If its canRun() method returns false, the command does not start and is removed from the EventScheduler.
 * Once a command starts, its initialize() method is called once and then its execute()
 * method is called repeatedly. After each time the execute() method is called, the
 * command's isFinished() method is called. The command stops running when isFinished() returns true.
 * After a command has finished, its end() method is called.
 *
 * Commands can also be removed from the EventScheduler by calling their stop() method. Calling the stop() method
 * will interrupt a command.
 *
 * When a command is interrupted, its interrupted() method is called and it is removed from the EventScheduler
 *
 * Subsystems that a command uses should be declared by calling the requires() method in its constructor.
 *
 * Every command has a priority which determines how it will interact with other commands.
 * If two commands use one or more of the same subsystems, the one with the higher priority will interrupt
 * the one with the lower priority if the lower priority command is already running, or prevent it from starting
 * if it has been added to the EventScheduler but has not yet started running.
 *
 * Default commands are special commands that have a priority of 0 (the lowest possible priority) and require only
 * one subsystem. Unlike regular commands, when they finish or are interrupted, they are not removed by the EventScheduler.
 * As a result, the EventScheduler continually attempts to run all default commands, and default commands
 * are constantly run while no other commands require the same subsystem. A command is a default command
 * if it is passed to a subsystem's setDefaultCommand() method. The subsystem that the default command requires
 * is automatically added to its list of requirements, so it is not necessary to use the requires() method to add it.
 */
class Command {
  private:
    /**
     * @brief Keeps track of which subsystems the command requires to run
     *
     * @htmlonly
     * <script>
     * var rows = document.querySelectorAll(".memItemRight");
     * for (var i = 0; i < rows.length; i++) {
	   *   let index = rows[i].innerHTML.indexOf("=0");
     *   if (index !== -1)
	   *     rows[i].innerHTML = rows[i].innerHTML.slice(0, index) + " = 0";
     * }
     * </script>
     * @endhtmlonly
     */
    std::vector<Subsystem*> subsystemRequirements;
  protected:
    /**
     * @brief Higher priority commands interrupt lower priority commands
     */
    int priority = 1;

    /**
     * @brief Adds a subsystem as one of a command's requirements
     * @param aSubsystem The subsystem that the command requires
     */
    void requires(Subsystem* aSubsystem);

    /**
     * @brief Keeps track of the status of the command
     */
    Status status = Status::Idle;

    /**
     * @brief Gets the requirements that a command uses
     *
     * Used by the EventScheduler to decide whether the command can run
     *
     * @return The command's requirements as a vector pointer
     */
    std::vector<Subsystem*>& getRequirements();

    /**
     * @brief Accesses commands' requires method
     */
    friend class Subsystem;

    /**
     * @brief Accesses commands' priority, status, and subsystem requirements
     */
    friend class EventScheduler;

    /**
     * @brief Acceses commands' status and subsystem requirements
     */
    friend class CommandGroup;
  public:
    /**
     * @brief The priority of a default command is 0
     */
    static const int DefaultCommandPriority = 0;

    /**
     * @brief Whether the Command can run or not
     *
     * Called by the EventScheduler before a Command starts running to check whether it can run or not
     *
     * @return Whether or not the Command can run
     */
    virtual bool canRun() = 0;

    /**
     * @brief Called once before the Command runs
     *
     * Code needed to sets up the Command for execution can be put here.
     * This method is called once before the Command begins running
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the command
     */
    virtual void execute() = 0;

    /**
     * @brief Called by the EventScheduler while the command is running to check if it is finished
     * @return Whether or not the command is finished
     */
    virtual bool isFinished() = 0;

    /**
     * @brief Runs once when command is finished
     */
    virtual void end() = 0;

    /**
     * @brief Runs once when a command is interrupted
     */
    virtual void interrupted() = 0;

    /**
     * @brief Runs once when a command is interrupted
     */
    virtual void blocked() = 0;

    /**
     * @brief Adds the command to the EventScheduler
     */
    virtual void run();

    /**
     * @brief Removes the command from the EventScheduler and interrupts it
     */
    virtual void stop();

    /**
     * @brief Creates a new Command
     * @return A Command
     */
    Command();
};

}; // namespace libIterativeRobot

#endif // _COMMANDS_COMMAND_H_
