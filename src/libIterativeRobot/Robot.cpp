#include "libIterativeRobot/Robot.h"
#include "libIterativeRobot/events/EventScheduler.h"
#include "libIterativeRobot/events/JoystickButton.h"
#include "libIterativeRobot/events/JoystickChannel.h"

#include "libIterativeRobot/commands/StopBase.h"
#include "libIterativeRobot/commands/StopLift.h"
#include "libIterativeRobot/commands/StopIntake.h"
#include "libIterativeRobot/commands/DriveWithJoy.h"
#include "libIterativeRobot/commands/LiftControl.h"
#include "libIterativeRobot/commands/IntakeControl.h"
#include "libIterativeRobot/commands/MoveLiftFor.h"
#include "libIterativeRobot/commands/MoveLiftTo.h"

#include "libIterativeRobot/commands/AutonGroup1.h"
#include "libIterativeRobot/commands/AutonGroup2.h"

Robot* Robot::instance = 0;

Base*  Robot::base = 0;
Lift*   Robot::lift = 0;
Intake*  Robot::intake = 0;

AutonChooser* Robot::autonChooser = 0;

pros::Controller* Robot::mainController = 0;
pros::Controller* Robot::partnerController = 0;

Robot::Robot() {
  printf("Overridden robot constructor!\n");
  // Initialize any subsystems
  base = new Base();
  lift  = new Lift();
  intake = new Intake();

  autonChooser = AutonChooser::getInstance();

  mainController = new pros::Controller(pros::E_CONTROLLER_MASTER);
  partnerController = new pros::Controller(pros::E_CONTROLLER_PARTNER);

  // Define buttons and channels
  libIterativeRobot::JoystickChannel* RightX = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_RIGHT_X);
  libIterativeRobot::JoystickChannel* LeftY = new libIterativeRobot::JoystickChannel(mainController, pros::E_CONTROLLER_ANALOG_LEFT_Y);
  libIterativeRobot::JoystickButton* LiftUp = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L1);
  libIterativeRobot::JoystickButton* LiftDown = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_L2);
  libIterativeRobot::JoystickButton* IntakeOpen = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R1);
  libIterativeRobot::JoystickButton* IntakeClose = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_R2);
  libIterativeRobot::JoystickButton* LiftToStart = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_DOWN);
  libIterativeRobot::JoystickButton* LiftToHorizontal = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_RIGHT);
  libIterativeRobot::JoystickButton* LiftToTop = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_UP);
  libIterativeRobot::JoystickButton* LiftToBack = new libIterativeRobot::JoystickButton(mainController, pros::E_CONTROLLER_DIGITAL_LEFT);

  // Add commands to be run to buttons
  RightX->setThreshold(50);
  LeftY->setThreshold(50);
  DriveWithJoy* driveCommand = new DriveWithJoy();
  RightX->whilePastThreshold(driveCommand);
  LeftY->whilePastThreshold(driveCommand);

  LiftUp->whileHeld(new LiftControl(true));
  LiftDown->whileHeld(new LiftControl(false));

  IntakeControl* intakeOpen = new IntakeControl(true);
  IntakeControl* intakeClose = new IntakeControl(false);
  IntakeOpen->whenPressed(intakeOpen);
  IntakeOpen->whenPressed(intakeClose, libIterativeRobot::Action::STOP);
  IntakeClose->whenPressed(intakeClose);
  IntakeClose->whenPressed(intakeOpen, libIterativeRobot::Action::STOP);
  IntakeOpen->whenReleased(intakeOpen, libIterativeRobot::Action::STOP);
  IntakeClose->whenReleased(intakeClose, libIterativeRobot::Action::STOP);

  LiftToStart->whenPressed(new MoveLiftTo(0));
  LiftToHorizontal->whenPressed(new MoveLiftTo(680));
  LiftToTop->whenPressed(new MoveLiftTo(1520));
  LiftToBack->whenPressed(new MoveLiftTo(2360));
}

void Robot::robotInit() {
  printf("Robot created.\n");
  autonChooser->addAutonCommand(new AutonGroup1(), "Auton 1");
}

void Robot::autonInit() {
  printf("Default autonInit() function\n");
  autonChooser->uninit();
  autonChooser->getAutonCommand()->run();
}

void Robot::autonPeriodic() {
  //printf("Default autonPeriodic() function\n");
  Motor::periodicUpdate();
  PIDController::loopAll();
}

void Robot::teleopInit() {
  printf("Default teleopInit() function\n");
  autonChooser->init();
}

void Robot::teleopPeriodic() {
  //printf("Default teleopPeriodic() function\n");
  Motor::periodicUpdate();
  PIDController::loopAll();
}

void Robot::disabledInit() {
  printf("Default disabledInit() function\n");
  autonChooser->uninit();
}

void Robot::disabledPeriodic() {
  //printf("Default disabledPeriodic() function\n");
}

Robot* Robot::getInstance() {
    if (instance == NULL) {
        instance = new Robot();
    }
    return instance;
}
