#ifndef _EVENTS_EVENTSCHEDULER_H_
#define _EVENTS_EVENTSCHEDULER_H_

#include "libIterativeRobot/commands/Command.h"
#include "libIterativeRobot/commands/CommandGroup.h"
#include "main.h"
#include "libIterativeRobot/events/EventListener.h"
#include "libIterativeRobot/subsystems/Subsystem.h"
#include <vector>
#include <algorithm>

namespace libIterativeRobot {

/**
 * The EventScheduler is in charge of executing Commands and CommandGroups. It handles the logic involved
 * in deciding which Commands should be running at any given time and which Commands should be interrupted.
 *
 * In order for the EventScheduler to function correctly, EventScheduler->getInstance()->update() must be called
 * repeatedly during the autonomous period and the teleop period.
 */

class EventScheduler {
  private:
    /**
     * @brief The number of subsystems being tracked by the EventScheduler
     */
    size_t numSubsystems = 0;

    /**
     * @brief An instance of the EventScheduler
     */
    static EventScheduler* instance;

    /**
     * @brief Creates an EventScheduler
     * @return An EventScheduler
     */
    EventScheduler();

    /**
     * @brief The subsystems the EventScheduler is tracking
     */
    std::vector<Subsystem*> subsystems;

    /**
     * @brief The Eventlisteners the EventScheduler is tracking
     */
    std::vector<EventListener*> eventListeners;

    /**
     * @brief A queue for Commands for the EventScheduler to process
     */
    std::vector<Command*> commandQueue;

    /**
     * @brief A queue for CommandGroups for the EventScheduler to process
     */
    std::vector<CommandGroup*> commandGroupQueue;

    /**
     * @brief Stores Commands after they are added to the EventScheduler.
     *
     * It acts as a buffer for the commandQueue, since undefined behavior can occur if Commands are added to it while
     * the EventScheduler is looping through it. Its contents are eventually added to the commandQueue.
     */
    std::vector<Command*> commandBuffer;

    /**
     * @brief Stores CommandGroups after they are added to the EventScheduler.
     *
     * It acts as a buffer for the commandGroupQueue, since undefined behavior can occur if CommandGroups are added
     * to it while the EventScheduler is looping through it. Its contents are eventuallt added to the commandGroupQueue
     */
    std::vector<CommandGroup*> commandGroupBuffer;

    /**
     *
     */
    std::vector<CommandGroup*> intermediateGroupBuffer;

    /**
     * @brief Stores Commands that the EventScheduler determines can run
     */
    std::vector<Command*> toExecute;

    /**
     * @brief Stores the indexes of Commands in the commandQueue that need to be run
     */
    std::vector<size_t> indexes;

    /**
     * @brief Whether or not the default Commands have been added to the EventScheduler yet
     */
    bool defaultAdded = false;

    /**
     * @brief Removes all Commands and CommandGroups from their respective buffers and queues
     */
    void clearScheduler();

    /**
     * @brief Checks if a given Command is in the EventScheduler
     *
     * Checks both the commandBuffer and commandQueue for the provided Command.
     *
     * @param aCommand The Command to search for
     * @return Whether the Command is found or not
     */
    bool commandInScheduler(Command* aCommand);

    /**
     * @brief Checks if a given CommandGroup is in the EventScheduler
     *
     * Checks both the commandGroupBuffer and commandGroupQueue for the provided CommandGroup.
     *
     * @param aCommandGroup The CommandGroup to search for
     * @return Whether the CommandGroup is found or not
     */
    bool commandGroupInScheduler(CommandGroup* aCommandGroup);

    /**
     * @brief Adds the commands in the commandBuffer to the commandQueue
     */
    void queueCommands();

    /**
     * @brief Adds the CommandGroups in the commandGroupBuffer to the intermediateGroupBuffer
     */
    void toIntermediateBuffer();

    /**
     * @brief Adds the CommandGroups in the intermediateGroupBuffer to the commandGroupQueue
     */
    void toGroupQueue();

    /**
     * @brief Adds the CommandGroups in the commandGroupBuffer to the commandGroupQueue
     */
    void queueCommandGroups();

    /**
     * @brief Runs checkConditions on all EventListeners
     */
    void checkEventListeners();

    /**
     * @brief Adds default commands if they have not yet been added
     */
    void addDefaultCommands();

    /**
     * @brief Schedules the CommandGroups in a given vector
     * @param commandGroups The vector to schedule CommandGroups from
     */
    void scheduleCommandGroups(std::vector<CommandGroup*>* commandGroups);
  public:
    /**
     * @brief Gets the singleton instance of the EventScheduler
     *
     * If the EventScheduler instance does not yet exist, it is created.
     *
     * @return The Event Scheduler instance
     */
    static EventScheduler* getInstance();

    /**
     * @brief Checks EventListeners and handles the logic for Commands and CommandGroups
     *
     * This functions is responsible for comparing the priorities of Commands and CommandGroups as well as their
     * requirements. If a Command shares a requirement with a higher priority Command, it cannot run. If it is already
     * running, it is interrupted. If a Command can run but it has not yet been executed, it is initialized. It is
     * then run and if it has finished, its end() method is called. The same logic is applied to CommandGroups.
     */
    void update();

    /**
     * @brief Adds an EventListener for the EventScheduler to keep track of
     * @param eventListener The EventListener to add
     */
    void addEventListener(EventListener* eventListener);

    /**
     * @brief Adds a Command to the EventScheduler
     *
     * The provided Command is stored in the commandBuffer until it can be added to the commandQueue
     *
     * @param commandToRun The Command to add
     */
    void addCommand(Command* command);

    /**
     * @brief Adds a CommandGroup to the EventScheduler
     *
     * The provided CommandGroup is stored in the commandGroupBuffer until it can be added to the commandGroupQueue
     *
     * @param commandGroupToRun The CommandGroup to add
     */
    void addCommandGroup(CommandGroup* commandGroup);

    /**
     * @brief Removes a Command from the EventScheduler
     *
     * The provided Command is interrupted, and then searched for in the commandBuffer and commandQueue. If it is found,
     * it is removed.
     *
     * @param command The Command to remove
     */
    void removeCommand(Command* command);

    /**
     * @brief Removes a CommandGroup from the EventScheduler
     *
     * The provided CommandGroup is interrupted, and then searched for in the commandGroupBuffer and Group. If it is
     * found, it is removed.
     *
     * @param commandGroup The CommandGroup to remove
     */
    void removeCommandGroup(CommandGroup* commandGroup);

    /**
     * @brief Adds a Subsystem for the EventScheduler to track
     * @param aSubsystem The Subsystem to track
     */
    void trackSubsystem(Subsystem* aSubsystem);

    /**
     * @brief Prepares the EventScheduler for the autonomous or teleop periods
     *
     * Removes all Commands and CommandGroups from the EventScheduler by calling the clearScheduler() method. Also
     * provides the option to not add default Commands
     *
     * @param noDefaultCommands Whether or not default Commands should be added. If true, default Commands are not
     * added, and if false, they are added
     */
    void initialize(bool noDefaultCommands = false);
};

};

#endif // _EVENTS_EVENTSCHEDULER_H_
