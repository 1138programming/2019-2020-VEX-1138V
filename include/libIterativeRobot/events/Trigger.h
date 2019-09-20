#ifndef _EVENTS_TRIGGER_H_
#define _EVENTS_TRIGGER_H_

#include "main.h"
#include "./EventListener.h"
#include "../commands/Command.h"
#include <vector>

namespace libIterativeRobot {

enum class Action {
  RUN,
  STOP,
};

/**
 * The Trigger class is used for running or stopping Commands and CommandGroups based on the state of the Trigger.
 *
 * The Trigger can be in one of two states: active, or inactive. It has four events associated with it. These
 * events are when the trigger is deactivated, or the transition from active to inactive; when the trigger is activated,
 * or the transition from inactive to active; when the trigger is active; and when the trigger is inactive. Each of
 * these events can run or stop Commands and CommandGroups. At least one of the events associated with the Trigger will
 * constantly be called, usually either the Trigger being inactive or active.
 */

class Trigger : public EventListener {
  private:
    /**
     * @brief Keeps track of the last state of the Trigger
     *
     * True corresponds to the Trigger's active state, and false corresponds to its inactive state
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
    bool lastState = false;

    /**
     * @brief Commands to run when the Trigger transitions from inactive to active
     */
    std::vector<Command*> runWhenActivatedCommands;

    /**
     * @brief Commands to run while the Trigger is active
     */
    std::vector<Command*> runWhileActiveCommands;

    /**
     * @brief Commands to run when the Trigger transitions from active to inactive
     */
    std::vector<Command*> runWhenDeactivatedCommands;

    /**
     * @brief Commands to run while the Trigger is inactive
     */
    std::vector<Command*> runWhileInactiveCommands;

    /**
     * @brief Commands to stop when the Trigger transitions from inactive to active
     */
    std::vector<Command*> stopWhenActivatedCommands;

    /**
     * @brief Commands to stop while the Trigger is active
     */
    std::vector<Command*> stopWhileActiveCommands;

    /**
     * @brief Commands to stop when the Trigger transitions from active to inactive
     */
    std::vector<Command*> stopWhenDeactivatedCommands;

    /**
     * @brief Commands to stop while the Trigger is inactive
     */
    std::vector<Command*> stopWhileInactiveCommands;
  protected:
    /**
     * @brief Creates a new Trigger
     * @return A Trigger
     */
    Trigger();

    /**
     * @brief Checks the Trigger's current state and last state
     *
     * Decides which Commands or CommandGroups, if any, to run or stop using the Trigger's current state and last state
     * This method is called repeatedly by the EventScheduler
     */
    void checkConditions();

    /**
     * @brief Sets a Command to be run or stopped when the Trigger is activated
     *
     * This method adds a Command to either the runWhenActivatedCommands or stopWhenActivatedCommands vectors.
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whenActivated(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped while the Trigger is active
     *
     * This method adds a Command to either the runWhileActiveCommands or stopWhileActiveCommands vectors.
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whileActive(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped when the Trigger is deactivated
     *
     * This method adds a Command to either the runWhenDeactivatedCommands or stopWhenDeactivatedCommands vectors.
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whenDeactivated(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped while the Trigger is inactive
     *
     * This method adds a Command to either the runWhileInactiveCommands or stopWhileInactiveCommands vectors.
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whileInactive(Command* command, Action action = Action::RUN); // Adds a command to be run while the trigger is inactive
  public:
    /**
     * @brief Gets the state of the Trigger
     *
     * Vitual function to allow for different types of Triggers. An example is the JoystickButton class which implements
     * the Trigger class.
     *
     * @return The state of the Trigger
     */
    virtual bool getState() = 0;
};

};

#endif // _EVENTS_TRIGGER_H_
