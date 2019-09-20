#ifndef _COMMANDS_COMMANDGROUP_H_
#define _COMMANDS_COMMANDGROUP_H_

#include "Command.h"
#include "main.h"
#include <vector>

namespace libIterativeRobot {

/**
 * A CommandGroup is a way to call commands in sequence or concurrently, or any combination of the two. It can be thought
 * of as consisting of a series of steps, with each step having one or more commands in it. All the commands in a step
 * are executed in parallel and the steps are executed in sequence. A command is added using the addSequentialCommand()
 * method, which adds a command into a new step. The addParallelCommand() method adds commands into the current last step.
 * A CommandGroup is also considered a command, so they can be added into other CommandGroups allowing for more complex
 * sequences of commands to be executed.
 *
 * A CommandGroup's requirements are all of the requirements of the commands in the step it is currently executing
 *
 * Commands and CommandGroups added can be set to be 'forgotten' by the CommandGroup. This means that the CommandGroup
 * will not wait for them to finish before moving on to the next sequential step.
 */

class CommandGroup : public Command {
  private:
    /**
     * @brief Holds all of the commands added to the CommandGroup
     *
     * 2d vector keeping track of all commands and command groups. Each vector in the 2d vector represents a
     * sequential step. All the commands and command groups in each sequential step are run in parallel
     */
    std::vector<std::vector<Command*>> commands;

    /**
     * @brief Keeps track of which Commands and CommandGroups have been added to the EventScheduler
     */
    std::vector<std::vector<int>> added;

    /**
     * @brief Keeps track of which Commands and CommandGroups the CommandGroup should forget
     */
    std::vector<std::vector<bool>> forget;

    /**
     * @brief The current sequential step the CommandGroup is running
     */
    size_t sequentialIndex = 0;

  protected:
    /**
     * @brief Adds a sequential Command or CommandGroup
     *
     * When this method is called, a new sequential step is added to which all subsequent parallel Commands are
     * a part of, until a new Command is added sequentially. This method should be called in the constructor.
     *
     * @param aCommand The Command or CommandGroup to be added sequentially
     * @param forget Whether or not the CommandGroup should forget about aCommand once it is added to the EventScheduler.
     * If true, the CommandGroup will not wait for aCommand to finish before moving on the next sequential step. The default
     * value is false
     */
    virtual void addSequentialCommand(Command* aCommand, bool forget = false);

    /**
     * @brief Adds a parallel Command or CommandGroup
     *
     * When this method is called, a Command or CommandGroup is added to the current sequential step. This method should
     * be called in the constructor.
     *
     * @param aCommand The Command or CommandGroup to be added in parallel
     * @param forget Whether or not the CommandGroup should forget about aCommand once it is added to the EventScheduler.
     * If true, the CommandGroup will not wait for aCommand to finish before moving on the next sequential step. The default
     * value is false.
     */
    virtual void addParallelCommand(Command* aCommand, bool forget = false);

  public:
    /**
     * @brief Whether the CommandGroup can run or not
     *
     * Checks if all the Commands and CommandGroups in the current sequential step can run by calling their CanRun methods
     * This is called by the EventScheduler before a CommandGroup starts running.
     * @return Whether or not the CommandGroup can run
     */
    virtual bool canRun();

    /**
     * @brief Called once before the CommandGroup runs
     *
     * Sets up the CommandGroup to run by setting the sequentialIndex to 0 and setting all of the added flags to false
     */
    virtual void initialize();

    /**
     * @brief Adds Commands and CommandGroups to the EventScheduler
     *
     * Goes through each sequential step and adds all of the Commands and CommandGroups. Also handles figuring out When
     * a sequential step has finished or when the CommandGroup has been interrupted
     */
    virtual void execute();

    /**
     * @brief Called by the EventScheduler while the CommandGroup is running to check if it is finished
     *
     * A CommandGroup is finished once it has executed all of its sequential steps. The method isFinished
     * checks whether sequentialIndex is greater than or equal to the number of sequential steps, and returns the result
     *
     * @return Whether or not the CommandGroup is finished
     */
    virtual bool isFinished();

    /**
     * @brief Runs when the CommandGroup is finished
     *
     * Sets the CommandGroup's status to Finished
     */
    virtual void end();

    /**
     * @brief Runs when a CommandGroup is interrupted
     *
     * Sets the CommandGroup's status to Idle and then stops all of the Commands and CommandGroups in the current
     * sequential step that triggerred the interruption
     */
    virtual void interrupted(); // Run when command group was interrupted

    virtual void blocked();

    /*
     * @brief Adds the CommandGroup to the EventScheduler
     */
    virtual void run();

    /*
     * @brief Removes the CommandGroup from the EventScheduler and interrupts it
     */
    virtual void stop();

    /**
     * @brief Creates a new CommandGroup
     * @return A CommandGroup
     */
    CommandGroup();
};

};

#endif // _COMMANDS_COMMANDGROUP_H_
