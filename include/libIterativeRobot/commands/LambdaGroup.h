#ifndef _COMMANDS_LAMBDAGROUP_H_
#define _COMMANDS_LAMBDAGROUP_H_

#include "libIterativeRobot/commands/CommandGroup.h"

namespace libIterativeRobot {
  class LambdaGroup : public CommandGroup {
    private:
    public:
      LambdaGroup();
      using CommandGroup::addSequentialCommand;
      using CommandGroup::addParallelCommand;
  };
}

#endif //_COMMANDS_LAMBDAGROUP_H_
