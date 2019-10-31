#include "AutonChooser.h"

size_t AutonChooser::numAutons;
std::vector<const char*> AutonChooser::autonNames;
std::vector<libIterativeRobot::Command*> AutonChooser::autonCommands;
size_t AutonChooser::autonIndex;

// LVGL Objects
lv_obj_t* AutonChooser::scrollLeft = NULL;
lv_obj_t* AutonChooser::autonName = NULL;
lv_obj_t* AutonChooser::scrollRight = NULL;

AutonChooser* AutonChooser::instance;

AutonChooser::AutonChooser() {
  autonIndex = 0;
  numAutons = 0;
}

lv_res_t AutonChooser::updateAutonName(lv_obj_t* btn) {
  if (btn == scrollRight) {
    if (autonIndex >= numAutons - 1)
      autonIndex = 0;
    else
      autonIndex++;
  } else if (btn == scrollLeft) {
    if (autonIndex <= 0)
      autonIndex = numAutons - 1;
    else
      autonIndex--;
  }
  printf("Auton is %d, size is %d\n", autonIndex, autonNames.size());
  pros::delay(1000);
  lv_label_set_text(autonName, autonNames[autonIndex]);
  return LV_RES_OK;
}

void AutonChooser::init() {
  if (scrollRight == NULL) {
    scrollRight = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t* scrollRightLabel = lv_label_create(scrollRight, NULL);
    lv_label_set_text(scrollRightLabel, ">");
    lv_btn_set_action(scrollRight, LV_BTN_ACTION_PR, updateAutonName);
    lv_obj_align(scrollRight, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0);

    autonName = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(autonName, autonNames[autonIndex]);
    lv_obj_align(autonName, NULL, LV_ALIGN_CENTER, 0, 0);

    scrollLeft = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_t* scrollLeftLabel = lv_label_create(scrollLeft, NULL);
    lv_label_set_text(scrollLeftLabel, "<");
    lv_btn_set_action(scrollLeft, LV_BTN_ACTION_PR, updateAutonName);
    lv_obj_align(scrollLeft, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
  }
}

void AutonChooser::uninit() {
  if (scrollRight != NULL) {
    lv_obj_del(scrollRight);
    lv_obj_del(autonName);
    lv_obj_del(scrollLeft);

    scrollRight = NULL;
    autonName = NULL;
    scrollLeft = NULL;
  }
}

void AutonChooser::addAutonCommand(libIterativeRobot::Command* command, const char* name) {
  numAutons++;
  autonCommands.push_back(command);
  autonNames.push_back(name);
}

libIterativeRobot::Command* AutonChooser::getAutonCommand() {
  return autonCommands[autonIndex];
}

AutonChooser* AutonChooser::getInstance() {
  if (instance == 0) {
    instance = new AutonChooser();
  } else {
    return instance;
  }
}
