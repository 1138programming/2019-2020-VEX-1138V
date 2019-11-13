#include "abstractBaseClasses/LinearProfiler.h"

LinearProfiler::LinearProfiler(Motor* outputMotor, double maxVel, double maxAccel, float kP, float kI, float kD) {
  this->outputMotor = outputMotor;
  this->maxVel = maxVel;
  this->maxAccel = maxAccel;
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;

  posPID = new PIDController(outputMotor, kP, kI, kD);
}

LinearProfiler::LinearProfiler(Motor* outputMotor, double maxVel, double maxAccel) {
  this->outputMotor = outputMotor;
  this->maxVel = maxVel;
  this->maxAccel = maxAccel;

  posPID = new PIDController(outputMotor, kP, kI, kD);
}

LinearProfiler::LinearProfiler(Motor* outputMotor) {
  this->outputMotor = outputMotor;

  posPID = new PIDController(outputMotor, kP, kI, kD);
}

void LinearProfiler::setMaxVel(double maxVel) {
  this->maxVel = maxVel;
}

void LinearProfiler::setMaxAccel(double maxAccel) {
  this->maxAccel = maxAccel;
}

void LinearProfiler::setThreshold(int threshold) {
  this->posPID->setThreshold(threshold);
}

void LinearProfiler::setTarget(int target) {
  this->target = target;
}

void LinearProfiler::setTargetRelative(int target) {
  this->target = getSensorValue() + target;
}

int LinearProfiler::getTarget() {
  return target;
}

void LinearProfiler::setSensorValue(int sensorValue) {
  posPID->setSensorValue(sensorValue);
}

int LinearProfiler::getSensorValue() {
  return posPID->getSensorValue();
}

PIDController* LinearProfiler::getPID() {
  return posPID;
}

void LinearProfiler::init() {
  /*int initial = getSensorValue();
  int distance = target - initial;

  // The middle point on the path
  int midpoint = abs(distance / 2) + initial;

  // Calculates the point at which the acceleration should become 0
  flatPoint = 0.5 * ((maxVel * maxVel) / maxAccel) + initial;

  // Checks to see if the target distance is long enough to get to the max velocity
  if (midpoint < flatPoint) {
    deccelPoint = midpoint;
  } else {
    deccelPoint = (target - (flatPoint)) + initial;
  }

  if (target > initial) {
    dir = 1;
    t_accel = maxAccel;
  } else {
    dir = -1;
    t_accel = -maxAccel;
  }*/

  initial = getSensorValue();
  distance = abs(target - initial);
  midPoint = distance / 2;
  flatPoint = (int)(0.5 * maxVel * maxVel / maxAccel);

  if (initial < target) {
    dir = 1;
    t_accel = maxAccel;
  } else {
    dir = -1;
    t_accel = -maxAccel;
  }

  if (midPoint > flatPoint) {
    deccelPoint = distance - flatPoint;
  } else {
    flatPoint = midPoint;
    deccelPoint = midPoint;
  }

  t_pos = 0;
  pidSetpoint = initial;
  posPID->setSetpoint(pidSetpoint);
  posPID->enable();

  dt = 0;
  vel = 0;
  accel = 0;
  lastTime = pros::millis() - 10;
  lastPos = initial;
  lastVel = 0;
}

void LinearProfiler::update() {
  std::uint32_t time = pros::millis();

  dt = int(time - lastTime);
  vel = (double)(getSensorValue() - lastPos) / dt;
  accel = (vel - lastVel) / dt;

  lastTime = time;
  lastPos = getSensorValue();
  lastVel = vel;

  //printf("%p: target pos: %f, target t_vel: %f, target t_accel: %f, pos: %d, t_vel: %f\n", this, pidSetpoint, t_vel, t_accel, getSensorValue(), ((double)deltaPos / dt));
  printf("%p: %f, %f, %f, %d, %f\n", this, t_pos, t_vel, t_accel, getSensorValue(), vel);

  /*if (fabs(pidSetpoint) < flatPoint) {
    t_accel = maxAccel * dir;
  } else if (fabs(pidSetpoint) < deccelPoint) {
    t_accel = 0;
  } else {
    t_accel = -maxAccel * dir;
  }

  t_vel += t_accel * dt;
  if (fabs(t_vel) > maxVel) {
    t_vel = maxVel * dir;
  }
  if (t_vel * dir < 0) {
    t_vel = 0;
    t_accel = 0;
  }

  pidSetpoint += t_vel * dt;*/

  if (t_pos < flatPoint) {
    t_accel = maxAccel;
  } else if (t_pos < deccelPoint) {
    t_accel = 0;
  } else {
    t_accel = -maxAccel;
  }
  t_vel += t_accel * dt;

  if (t_vel > maxVel) {
    t_vel = maxVel;
    t_accel = 0;
  } else if (t_vel < 0) {
    t_vel = 0;
    t_accel = 0;
  }
  t_pos += t_vel * dt;

  pidSetpoint = dir * t_pos + initial;
  posPID->setSetpoint(pidSetpoint);

  //printf("%p: %d\n", this, (int)pidSetpoint);
}

bool LinearProfiler::atTarget() {
  if (abs(getSensorValue()) > deccelPoint) {
    return (t_vel == 0 && posPID->atSetpoint());
  }
  return false;
}

void LinearProfiler::stop() {
  posPID->disable();
}

int LinearProfiler::getOutput() {
  return posPID->getOutput();
}

int LinearProfiler::getTargetPos() {
  return (int)pidSetpoint;
}

double LinearProfiler::getTargetVel() {
  return t_vel;
}

double LinearProfiler::getTargetAccel() {
  return t_accel;
}

int LinearProfiler::getPos() {
  return getSensorValue();
}

double LinearProfiler::getVel() {
  return vel;
}

double LinearProfiler::getAccel() {
  return accel;
}

int LinearProfiler::getDeltaTime() {
  return dt;
}
