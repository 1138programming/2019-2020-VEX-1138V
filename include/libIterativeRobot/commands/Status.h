#ifndef _COMMANDS_STATUS_H_
#define _COMMANDS_STATUS_H_

namespace libIterativeRobot {
  /**
   * The Status of a command indicates what the EventScheduler should do with it. An Idle status means that the command
   * has not yet been initialized. Once initialized, a command's status is set to Running. After a command's isFinished
   * function returns true, the command's status is set to Finished. If a command is interrupted, its status is set to
   * Interrupted
   */
  enum class Status {
    Idle = 0,
    Running,
    Finished,
    Interrupted,
    Blocked
  };
}

#endif // _COMMANDS_STATUS_H_
