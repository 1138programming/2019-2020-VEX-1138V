#ifndef _EVENTS_JOYSTICKCHANNEL_H_
#define _EVENTS_JOYSTICKCHANNEL_H_

#include "api.h"
#include "main.h"
#include "./Trigger.h"
#include "../commands/Command.h"

namespace libIterativeRobot {

/**
 * The JoystickChannel class is used to run and stop Commands and CommandGroups using a joystick channel.
 * It implements the Trigger class and inherits all of its events. The events associated with it are: when the channel
 * passes a threshold forwards, while the channel is past the threshold, when the channel passes the threshold
 * backwards, and while the button is within the threshold.
 */

class JoystickChannel : public Trigger {
  private:
    /**
     * @brief The Controller that the channel is on
     */
    pros::Controller* controller;

    /**
     * @brief The channel with which the Trigger's state is associated with
     */
    pros::controller_analog_e_t channel;

    /**
     * @brief The value of the threshold to check the joystick channel's value against
     */
    std::int32_t threshold = kDefaultThreshold;
  protected:
  public:
    /**
     * @brief The default threshold value is 10
     */
    static const std::int32_t kDefaultThreshold = 10;

    /**
     * @brief Creates a new JoystickChannel
     * @param controller The Controller to read the value of the channel from
     * @param channel The channel to read
     * @return A JoystickChannel
     */
    JoystickChannel(pros::Controller* controller, pros::controller_analog_e_t channel);

    /**
     * @brief Checks if the channel is past the threshold
     * @return True if the channel is past the threshold, false if it is within the threshold
     */
    bool getState();

    /**
     * @brief Sets a Command to be run or stopped when the channel passes the threshold in the forwards direction
     *
     * Calls the whenActivated() method from the Trigger class with the same parameters
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whenPassingThresholdForward(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped while the channel is past the threshold
     *
     * Calls the whileActive() method from the Trigger class with the same parameters
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whilePastThreshold(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped when the button is released
     *
     * Calls the whenDeactivated() method from the Trigger class with the same parameters
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whenPassingThresholdReverse(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets a Command to be run or stopped while the joystick is within the threshold
     *
     * Calls the whileInactive() method from the Trigger class with the same parameters
     *
     * @param command The Command to be added
     * @param action Specifies whether to run or stop the command. The default value is Action::RUN
     */
    void whileWithinThreshold(Command* command, Action action = Action::RUN);

    /**
     * @brief Sets the threshold to use
     * @param threshold The value to use as the threshold
     */
    void setThreshold(std::int32_t threshold);
};

};

#endif // _EVENTS_JOYSTICKCHANNEL_H_
