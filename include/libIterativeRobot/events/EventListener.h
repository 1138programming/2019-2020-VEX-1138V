#ifndef _EVENTS_EVENTLISTENER_H_
#define _EVENTS_EVENTLISTENER_H_

#include "main.h"

namespace libIterativeRobot {

/**
 * The EventListener class is the base class for event listeners such as the Trigger class. When an addEventListener
 * is instantiated, it is automatically added to the EventScheduler, which calls its checkConditions method repeatedly.
 * This is used to run or stop Commands or CommandGroups when certain conditions are met.
 */

class EventListener {
  private:
  protected:
    /**
     * @brief Creates a new EventListener
     * @return An EventListener
     *
     * Adds itself to the EventScheduler to be checked repeatedly
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
    EventListener();

    /**
     * @brief Called repeatedly by the EventScheduler
     *
     * Should be used to run Commands or CommandGroups when certain conditions are met, specified by classes
     * implementing checkConditions
     */
    virtual void checkConditions() = 0;
  public:
  /**
   * Accesses the checkConditions() method;
   */
  friend class EventScheduler;
};

};

#endif // _EVENTS_EVENTLISTENER_H_
