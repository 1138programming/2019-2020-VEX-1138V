#include "abstractBaseClasses/PIDController.h"

std::vector<PIDController*> PIDController::instances; //  All values are initialized to 0

PIDController::PIDController(Motor* outputMotor, float kP, float kI, float kD) {
  this->outputMotor = outputMotor;
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  addInstance();

  pastErrors = NULL;
}

PIDController::PIDController(float kP, float kI, float kD) {
  this->outputMotor = NULL;
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  addInstance();

  pastErrors = NULL;
}

void PIDController::addInstance() {
  instances.push_back(this);
}

void PIDController::setKp(float kP) {
  this->kP = kP;
}

void PIDController::setKi(float kI) {
  this->kI = kI;
}

void PIDController::setKd(float kD) {
  this->kD = kD;
}

void PIDController::setSetpoint(int setpoint) {
  //printf("Setpoint set to %d\n", setpoint);
  this->setpoint = setpoint;
  integral = 0;
}

void PIDController::setSetpointRelative(int setpoint) {
  this->setpoint = getSensorValue() + setpoint;
}

int PIDController::getSetpoint() {
  return this->setpoint;
}

/*void PIDController::setSensorEncoder(pros::ADIEncoder* encoder) {
  this->encoder = encoder;
  this->IMEaddress = 0;
  this->IMEset = false;
}*/

/*void PIDController::setSensorIME(unsigned char IMEaddress) {
  this->IMEaddress = IMEaddress;
  this->IMEset = true;
  this->encoder = NULL;
}*/

void PIDController::setSensorValue(int sensorValue) {
  currSensorValue = sensorValue;
}

int PIDController::getSensorValue() {
  if (outputMotor == NULL) {
    return currSensorValue;
  }
  return (int)outputMotor->getEncoderValue();
}

int PIDController::getOutput() {
  return output;
}

void PIDController::setThreshold(int threshold) {
  this->threshold = threshold;
}

void PIDController::loop() {
  if (pastErrors == NULL) {
    printf("PID was looped before being initialized\n");
    init();
    //enabled = false;
    //return;
  }
  //printf("PID is looping\n");
  currSensorValue = getSensorValue();
  deltaTime = pros::millis() - lastTime;

  // Calculates error
  error = setpoint - currSensorValue;

  // Calculates the derivative
  derivative  = (error - (*pastErrors)[lastErrorIndex]) / (deltaTime / 5);
  // printf("Error is %d and past error is %d\n", error, (*pastErrors)[lastErrorIndex]);

  // int secondToLastError = lastErrorIndex - 1;
  // if (secondToLastError < 0)
  //   secondToLastError = numErrors - 1;

  // derivative = (((*pastErrors)[secondToLastError] + (*pastErrors)[lastErrorIndex]) / 2) - error;

  // printf("Last error index is %d, lastError is %d\n", lastErrorIndex, (*pastErrors)[lastErrorIndex]);

  // Update the position of the last error in the pastErrors vector
  lastErrorIndex++;
  if (lastErrorIndex >= numErrors)
   lastErrorIndex = 0;
  //(*pastErrors)[lastErrorIndex] = (int)(error * (deltaTime / 5));
  (*pastErrors)[lastErrorIndex] = error;

  int oldestError = lastErrorIndex + 1;
  if (oldestError >= numErrors)
    oldestError = 0;

  // Calculates the integral
  integral += (*pastErrors)[lastErrorIndex] - (*pastErrors)[oldestError];
  //printf("Current error is %d, oldestError is %d\n", (*pastErrors)[lastErrorIndex], (*pastErrors)[oldestError]);

  // Calculates the output
  output = (int)(kP * error + kI * integral + kD * derivative);
  output = confineToRange(output, minOutput, maxOutput);
  //printf("Current sensor value is %d, error is %d, integral is %d, derivative is %f, and output is %d\n", currSensorValue, error, integral, derivative, output);
  //printf("Error is %d and output is %d\n", error, output);

  if (outputMotor != NULL) {
    outputMotor->setSpeed(output);
  }

  lastTime = pros::millis();
}

void PIDController::lock() {
  setSetpoint(getSensorValue());
}

void PIDController::setOutputRange(int minOutput, int maxOutput) {
  this->minOutput = minOutput;
  this->maxOutput = maxOutput;
}

bool PIDController::atSetpoint() {
  currSensorValue = getSensorValue();
  bool range = inRange(currSensorValue, setpoint - threshold, setpoint + threshold);
  bool smallDerivative = fabs(derivative) < maxDerivative;
  bool atSetpoint = range && smallDerivative; // Checks if the sensor value is within a threshold of the target and whether the derivative is less than 0.1
  return atSetpoint;
}

void PIDController::enable() {
  init();
  enabled = true;
  printf("PID enabled\n");
}

void PIDController::disable() {
  stop();
  printf("PID disabled\n");
}

bool PIDController::isEnabled() {
  return enabled;
}

void PIDController::init() {
  pastErrors = new std::vector<int>();

  // Initializes all values in the past errors array to the current error
  int error = setpoint - getSensorValue();
  for (int i = 0; i < numErrors; i++) {
    pastErrors->push_back(error);
  }

  lastTime = pros::millis();
  lastErrorIndex = 1;
  integral = error * numErrors;
}

void PIDController::stop() {
  enabled = false;
  //std::vector<int>().swap(pastErrors);
  pastErrors = NULL;
  delete pastErrors;
}

void PIDController::loopAll() {
  //printf("Enabled flags are");
  //printf("Number of loops is %d\n", instances.size());
  for (size_t i = 0; i < instances.size(); i++) {
    //printf(", %d", instances[i]->enabled);
    if (instances[i]->enabled) {
      instances[i]->loop();
    }
  }
  //printf("\n");
}
