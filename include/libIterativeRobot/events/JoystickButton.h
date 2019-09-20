#ifndef _EVENTS_JOYSTICKBUTTON_H_
#define _EVENTS_JOYSTICKBUTTON_H_

#include "main.h"
#include "./Trigger.h"
#include "../commands/Command.h"
#include <vector>

namespace libIterativeRobot {

/**
 * The JoystickButton class is used to run and stop Commands and CommandGroups using a joystick button.
 * It implements the Trigger class and inherits all of its events. The events associated with it are: when the button
 * is pressed, while the button is being held, when the button is released, and while the button is released.
 */

class JoystickButton : public Trigger {
  private:
    /**
     * @brief The Controller that the button is on
     */
    pros::Controller* controller;

    /**
     * @brief The button with which the Trigger's state is associated with
     */
    pros::controller_digital_e_t button;
  protected:
  public:
    /**
     * @brief Creates a new JoystickButton
     * @param controller The Controller to read the state of the button from
     * @param button The button to read
     * @return A JoystickButton
     */
    JoystickButton(pros::Controller* controller, pros::controller_digital_e_t button);

    /**
     * @brief Gets the state of the button
     * @return True if the button is pressed, false otherwise
     */
    bool getState();

    /**
     * @brief Sets a Command to be run or stopped when the button is pressed
     *
     * Calls the whenActivated() method from the Trigger class with the same parameters
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whenPressed(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped while the button is being held
     *
     * Calls the whileActive() method from the Trigger class with the same parameters
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whileHeld(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped when the button is released
     *
     * Calls the whenDeactivated() method from the Trigger class with the same parameters
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whenReleased(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped while the button is released
     *
     * Calls the whileInactive() method from the Trigger class with the same parameters
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whileReleased(Command* command, Action action = Action::RUN);
};

};

#endif // _EVENTS_JOYSTICKBUTTON_H_
