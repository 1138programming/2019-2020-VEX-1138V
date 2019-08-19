#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/events/EventScheduler.h"
#include "libIterativeRobot/events/JoystickButton.h"
#include "libIterativeRobot/events/JoystickChannel.h"

#include "libIterativeRobot/commands/StopBase.h"
#include "libIterativeRobot/commands/StopAngler.h"
#include "libIterativeRobot/commands/StopIntake.h"
#include "libIterativeRobot/commands/DriveWithJoy.h"
#include "libIterativeRobot/commands/AnglerControl.h"
#include "libIterativeRobot/commands/IntakeControl.h"
#include "libIterativeRobot/commands/MoveAnglerFor.h"
#include "libIterativeRobot/commands/MoveAnglerTo.h"

#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/AutonGroup2.h"

Base*  Robot::base = 0;
Angler*   Robot::angler = 0;
Intake*  Robot::intake = 0;

AutonChooser* Robot::autonChooser = 0;

pros::Controller* Robot::mainController = 0;
pros::Controller* Robot::partnerController = 0;

Robot::Robot() {
  printf("Overridden robot constructor!\n");
  autonGroup = NULL;
  // Initialize any subsystems
  base = new Base();
  angler  = new Angler();
  intake = new Intake();

  autonChooser = AutonChooser::getInstance();

  mainController = new pros::Controller(pros::E_CONTROLLER_MASTER);
  partnerController = new pros::Controller(pros::E_CONTROLLER_PARTNER);

  // Define buttons and channels
  libIterativeRobot::JoystickChannel* RightY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  libIterativeRobot::JoystickChannel* LeftY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_Y);
  libIterativeRobot::JoystickButton* AnglerUp = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R1);
  libIterativeRobot::JoystickButton* AnglerDown = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R2);
  libIterativeRobot::JoystickButton* IntakeOpen = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L1);
  libIterativeRobot::JoystickButton* IntakeClose = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L2);
  libIterativeRobot::JoystickButton* AnglerToStart = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_DOWN);
  libIterativeRobot::JoystickButton* AnglerToHorizontal = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_RIGHT);
  libIterativeRobot::JoystickButton* AnglerToTop = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_UP);
  libIterativeRobot::JoystickButton* AnglerToBack = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_LEFT);

  // Add commands to be run to buttons
  RightY->setThreshold(50);
  LeftY->setThreshold(50);
  DriveWithJoy* driveCommand = new DriveWithJoy();
  RightY->whilePastThreshold(driveCommand);
  LeftY->whilePastThreshold(driveCommand);

  AnglerUp->whileHeld(new AnglerControl(true));
  AnglerDown->whileHeld(new AnglerControl(false));

  IntakeControl* intakeOpen = new IntakeControl(true);
  IntakeControl* intakeClose = new IntakeControl(false);
  IntakeOpen->whenPressed(intakeOpen);
  IntakeOpen->whenPressed(intakeClose, libIterativeRobot::STOP);
  IntakeClose->whenPressed(intakeClose);
  IntakeClose->whenPressed(intakeOpen, libIterativeRobot::STOP);
  IntakeOpen->whenReleased(intakeOpen, libIterativeRobot::STOP);
  IntakeClose->whenReleased(intakeClose, libIterativeRobot::STOP);

  AnglerToStart->whenPressed(new MoveAnglerTo(0));
  AnglerToHorizontal->whenPressed(new MoveAnglerTo(680));
  AnglerToTop->whenPressed(new MoveAnglerTo(1520));
  AnglerToBack->whenPressed(new MoveAnglerTo(2360));
}

void Robot::robotInit() {
  printf("Robot created.\n");
}

void Robot::autonInit() {
  printf("Default autonInit() function\n");
  libIterativeRobot::EventScheduler::getInstance()->initialize();
  autonChooser->uninit();

  switch (autonChooser->getAutonChoice()) {
    case 0:
      printf("Running group %d\n", 1);
      autonGroup = new AutonGroup1();
      break;
    case 1:
      printf("Running group %d\n", 2);
      autonGroup = new AutonGroup2();
      break;
  }
  autonGroup->run();
}

void Robot::autonPeriodic() {
  //printf("Default autonPeriodic() function\n");
  libIterativeRobot::EventScheduler::getInstance()->update();
  Motor::periodicUpdate();
  PIDController::loopAll();
}

lv_res_t Robot::print(lv_obj_t* roller) {
  char* optionName = new char[128]();
  lv_roller_get_selected_str(roller, optionName);
  printf("Option selected is called ");
  printf(optionName);
  printf("\n");
  return LV_RES_OK;
}

void Robot::teleopInit() {
  printf("Default teleopInit() function\n");
  libIterativeRobot::EventScheduler::getInstance()->initialize();
  //autonChooser->init();

  //autonGroup = new AutonGroup1();
  //autonGroup->run();
}

void Robot::teleopPeriodic() {
  //printf("Default teleopPeriodic() function\n");
  libIterativeRobot::EventScheduler::getInstance()->update();
  Motor::periodicUpdate();
  PIDController::loopAll();
}

void Robot::disabledInit() {
  printf("Default disabledInit() function\n");
  libIterativeRobot::EventScheduler::getInstance()->initialize();
  autonChooser->uninit();
}

void Robot::disabledPeriodic() {
  //printf("Default disabledPeriodic() function\n");
}
