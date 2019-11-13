#ifndef LINEARPROFILER_H_
#define LINEARPROFILER_H_

#include "abstractBaseClasses/PIDController.h"
#include "abstractBaseClasses/Motor.h"

class LinearProfiler {
  private:
    Motor* outputMotor;
    PIDController* posPID;

    std::uint32_t lastTime = 0;
    int lastPos = 0;
    double lastVel = 0;

    double vel = 0;
    double accel = 0;

    int dt = 0;

    double maxAccel = 0.01;
    double maxVel = 3.0;

    double t_accel = 0;
    double t_vel = 0;
    double t_pos = 0;
    int pidSetpoint = 0;

    int initial = 0;
    int flatPoint = 0;
    int midPoint = 0;
    int deccelPoint = 0;
    int target = 0;
    int distance = 0;

    int dir = 0;
  protected:
  public:
    float kP = 0.45;
    float kI = 0;
    float kD = 0;

    LinearProfiler(Motor* outputMotor, double maxVel, double maxAccel, float kP, float kI, float kD);
    LinearProfiler(Motor* outputMotor, double maxVel, double maxAccel);
    LinearProfiler(Motor* outputMotor);

    // Functions to set constants
    void setMaxVel(double maxVel);
    void setMaxAccel(double maxAccel);
    void setThreshold(int threshold);

    // Target functions
    void setTarget(int target);
    void setTargetRelative(int target);
    int getTarget();

    // Sensor functions
    void setSensorValue(int sensorValue);
    int getSensorValue();

    // PID Functions
    PIDController* getPID();

    // Functions that move the motor
    void init();
    void update();
    bool atTarget();
    void stop();

    // Getters for internal variables
    int getOutput();
    int getTargetPos();
    double getTargetVel();
    double getTargetAccel();
    int getPos();
    double getVel();
    double getAccel();
    int getDeltaTime();
};

#endif
