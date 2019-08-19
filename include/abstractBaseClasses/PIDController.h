#ifndef _SUBSYSTEMS_PIDCONTROLLER_H_
#define _SUBSYSTEMS_PIDCONTROLLER_H_

#include "Motor.h"
#include <vector>

class PIDController {
  private:
    // PID constants
    float kP = 0;
    float kI = 0;
    float kD = 0;

    // Motor to use the PID output with
    Motor* outputMotor;

    // Integers to hold the error, integal, and derivative value of the loop
    int integral = 0;
    float derivative = 0;
    int error = 0;

    // Vector to hold psat error values, and other variables to hold the index of the last error value and the number of past error values to record
    std::vector<int>* pastErrors;
    int numErrors = 30;
    int lastErrorIndex = 0;

    int output = 0; // Output of the PID loop
    int setpoint = 0; // Setpoint to get to

    int currSensorValue = 0; // If no motor is given, this must be set manually
    int threshold = 15; // Default value of the threshold for the error at the setpoint
    float maxDerivative = 0.05; // Default value for the maximum value of the derivaitve at the setpoint
    int deltaTime = 0; // Time between loops
    int lastTime = 0; // Time recorded in the last loop
    int minOutput = -KMaxMotorSpeed; // Default is -KMaxMotorSpeed
    int maxOutput = KMaxMotorSpeed; // Default is KMaxMotorSpeed
    static std::vector<PIDController*> instances; // A vector to contain all PIDController instances
    bool enabled = false; // If the loop is enabled it will loop when loopAll is called
    void addInstance();
  public:
    PIDController(Motor* motorChannel, float kP = 1, float kI = 0, float kD = 0); // Initializes a PID controller with a motor
    PIDController(float kP = 1, float kI = 0, float kD = 0); // Initializes a PID controller without a motor
    void setKp(float kP); // Sets P value
    void setKi(float kI); // Sets I value
    void setKd(float kD); // Sets D value
    void setSetpoint(int setpoint); // Sets the setpoint to the given value
    void setSetpointRelative(int setpoint); // Adds the given value to the setpoint
    int getSetpoint(); // Returns the current setpoint
    void setSensorValue(int sensorValue); // Sets currSensorValue for use by the PID loop
    int getSensorValue(); // Gets the value of the motor's encoder or the value of currSensorValue if no motor is provided
    int getOutput(); // Gets the value of output calculated by the loop function
    void setThreshold(int threshold); // Sets the value of the threshold for use when calculating if the PID loop is at its setpoint
    bool atSetpoint(); // Returns if the PID loop has reached the setpoint
    void loop(); // Does all calculations
    void lock(); // Sets the setpoint to the current sensor value
    void setOutputRange(int minSpeed, int maxSpeed); // Sets the minimum and maximum values that the PID can calculate as the output
    void enable();
    void disable();
    bool isEnabled();
    void init();
    void stop();
    static void loopAll();
};

#endif
