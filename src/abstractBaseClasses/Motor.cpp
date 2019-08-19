#include "abstractBaseClasses/Motor.h"

Motor* Motor::motorInstances[MAX_MOTORS];

Motor::Motor(std::uint8_t port, pros::motor_gearset_e_t gearset) {
  this->port = port;
  motorType = v5;

  // Set defaults
  this->gearset = gearset;
  encoderUnits = globalEncoderUnits;
  brakeMode = globalBrakeMode;
  speed = 0;
  slewedSpeed = 0;
  slewStep = globalSlewStep;
  reversed = false;
  following = false;
  master = NULL;

  v5Motor = new pros::Motor(port, gearset, reversed, encoderUnits);
  v5Motor->set_brake_mode(brakeMode);

  // Initialize all elements in the followers array to null
  //numFollowers = MAX_FOLLOWERS;
  /*for (unsigned int i = 0; i < numFollowers; i++) {
    followers[i] = NULL;
  }*/
}

Motor::Motor(Port port) {
  this->port = (std::uint8_t)port - 21;
  motorType = v4;

  speed = 0;
  slewedSpeed = 0;
  slewStep = globalSlewStep;
  reversed = false;
  following = false;
  master = NULL;

  v4Motor = new pros::ADIMotor(this->port);
}

// Set a master motor
void Motor::setMaster(Motor* motor) {
  following = true;
  master = motor;
}

// Initialize motorInstances array with motor instances
void Motor::init() {
  for (std::uint8_t i = 0; i < MAX_MOTORS; i++) {
    motorInstances[i] = NULL;
  }
}

Motor* Motor::getMotor(std::uint8_t port, pros::motor_gearset_e_t gearset) {
  if (motorInstances[(int)port - 1] == NULL) {
    motorInstances[(int)port - 1] = new Motor(port, gearset);
  }
  return motorInstances[(int)port - 1];
}

Motor* Motor::getMotor(Port port) {
  if (motorInstances[port - 1] == NULL) {
    motorInstances[port - 1] = new Motor(port);
  }
  return motorInstances[port - 1];
}

// Sets the speed of the motor
void Motor::setSpeed(int speed) {
  // If this motor is a follower, setSpeed does nothing
  if (following)
    return;

  // Set the speed of the follower motors to the same speed
  // for (unsigned int i = 0; i < numFollowers; i++) {
  //     if (followers[i] != NULL) {
  //       followers[i]->speed = speed;
  //     }
  // }
  this->speed = speed;
  for (Motor* follower : followers) {
    follower->speed = speed;
  }
}

void Motor::setSlewStep(int slewStep) {
  this->slewStep = slewStep;
}

void Motor::enableSlewing() {
  slew = true;
}

void Motor::enableSlewing(int slewStep) {
  this->slewStep = slewStep;
  slew = true;
}

void Motor::disableSlewing() {
  slew = false;
}

void Motor::setThreshold(int threshold) {
  this->threshold = threshold;
}

void Motor::reverse() {
  reversed = true;
  if (motorType == v5) {
    v5Motor->set_reversed(reversed);
  }
}

void Motor::setEncoder(pros::ADIEncoder* encoder) {
  this->encoder = encoder;
}

void Motor::resetEncoder() {
  if (motorType == v5) {
    v5Motor->tare_position();
  } else {
    if (encoder != NULL)
      encoder->reset();
  }
}

void Motor::addFollower(Motor* motor) {
  // Cannot add followers to a follower
  if (following)
    return;

  // Set all of the followers of the follower to null
  /*for (unsigned int i = 0; i < motor->numFollowers; i++) {
    if (motor->followers[i] != NULL)
      return;
  }*/
  motor->followers.clear();

  // Add the follower to the followers array and set the follower's master to this motor
  // for (unsigned int i = 0; i < numFollowers; i++) {
  //   if (followers[i] == NULL) {
  //     followers[i] = motor;
  //     motor->setMaster(this);
  //     return;
  //   }
  // }
  followers.push_back(motor);
  motor->setMaster(this);
}

// Return the speed of the motor
int Motor::getSpeed() {
  return following ? master->getSpeed() : speed;
}

int Motor::getSlewedSpeed() {
  return following ? master->getSlewedSpeed() : slewedSpeed;
}

// Return the motor port
int Motor::getPort() {
  return port;
}

double Motor::getEncoderValue() {
  if (motorType == v5) {
    return v5Motor->get_position();
  } else {
    if (encoder != NULL)
      return (double)encoder->get_value();
  }
  return 0;
}

std::int32_t Motor::getRawEncoderValue() {
  if (motorType == v5) {
    std::uint32_t time = pros::millis();
    return v5Motor->get_raw_position(&time);
  } else {
    if (encoder != NULL)
      return encoder->get_value();
  }
  return 0;
}

// Returns a MotorType, either v4 or v5
MotorType Motor::getMotorType() {
  return motorType;
}

pros::Motor* Motor::getMotorObject() {
  return this->v5Motor;
}

int Motor::updateSlewRate(int targetSpeed) {
  // A bit of motor slewing to make sure that we don't stall
  int deltaSpeed = targetSpeed - slewedSpeed;
  int sign = deltaSpeed < 0 ? -1 : 1;
  if (abs(deltaSpeed) > slewStep) {
    slewedSpeed += slewStep * sign;
  } else {
    slewedSpeed = targetSpeed;
  }

  return slewedSpeed;
}

void Motor::move() {
  if (motorType == v4) {
    if (slew)
      v4Motor->set_value(updateSlewRate(speed));
    else
      v4Motor->set_value(speed);
  } else {
    if (slew)
      v5Motor->move(updateSlewRate(speed));
    else
      v5Motor->move(speed);
  }
}

void Motor::periodicUpdate() {
  //printf("Updating motors\n");
  for (int i = 0; i < MAX_MOTORS; i++) {
    if (motorInstances[i] != NULL) {
      motorInstances[i]->move();
    }
  }
}

void Motor::resetEncoders() {
  printf("Resetting encoders\n");
  for (int i = 0; i < MAX_MOTORS; i++) {
    if (motorInstances[i] != NULL)
      motorInstances[i]->resetEncoder();
  }
}
