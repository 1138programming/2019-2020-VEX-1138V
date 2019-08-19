#ifndef MOTOR_H
#define MOTOR_H

#include "api.h"
#include "Constants.h"
#include "common.h"
#include <vector>

enum Port {
  A = 22,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
};

enum MotorType {
  v4,
  v5,
};

class Motor {
  private:
    std::uint8_t port; // Motor port
    pros::motor_gearset_e_t gearset; // v5 motor gearset
    pros::motor_encoder_units_e_t encoderUnits; // v5 motor encoder units
    pros::motor_brake_mode_e_t brakeMode;

    int currSpeed; // Used by updateSlew Rate
    int speed; // Speed of the motor
    int slewedSpeed; // Speed of the motor taking its slew step into account
    int slewStep; // Maximum value that the motor's speed can increase or decrease by in one update cycle
    bool reversed = false;
    int threshold = 5;
    bool slew = false;

    //Motor* followers[MAX_FOLLOWERS]; // Array containing the motor's followers
    std::vector<Motor*> followers; // Vector containing the motor's followers
    //unsigned int numFollowers; // Number of followers
    Motor* master; // Pointer to master motor
    bool following; // True if the motor is a follower, false otherwise
    void setMaster(Motor* motor); // Sets a motor to be a master motor

    MotorType motorType; // Type of motor
    pros::Motor* v5Motor; // Pointer to v5 motor object
    pros::ADIMotor* v4Motor; // Pointer to v4 motor object
    pros::ADIEncoder* encoder; // Pointer to encoder object for v4 motors

    static Motor* motorInstances[MAX_MOTORS]; // Array of all motor instances

    Motor(std::uint8_t port, pros::motor_gearset_e_t gearset); // Constructor, takes a port
    Motor(Port port);
  public:
    // These functions are used to initialize and access the motor object
    static void init(); // Initializes motor objects
    static Motor* getMotor(std::uint8_t port, pros::motor_gearset_e_t gearset); // Gets a motor on the specified port, between ports 1-22
    static Motor* getMotor(Port port); // Gets a motor on the specified port, between ports A-H

    // These functions change something about the motor object
    void setSpeed(int speed); // Sets the speed of the motor
    void setSlewStep(int slewStep);
    void enableSlewing();
    void enableSlewing(int slewStep);
    void disableSlewing();
    void setThreshold(int threshold); // Sets a threshold for the motor's speed
    void reverse(); // Reverses the motor
    void setEncoder(pros::ADIEncoder* encoder); // Sets an encoder to be used for v4 motors in place of a built in encoder
    void resetEncoder();
    void addFollower(Motor* motor); // Adds a follower to the motor

    // These functions get something from the motor object
    int getSpeed(); // Gets the last speed set
    int getSlewedSpeed();
    int getTheshold(); // Gets the motor's threshold
    int getPort(); // Gets the motor's port
    double getEncoderValue(); // Gets the encoder value of a v5 motor in the encoder units it uses
    std::int32_t getRawEncoderValue(); // Gets the raw encoder value of the motor
    MotorType getMotorType(); // Gets the type of motor
    pros::Motor* getMotorObject();

    // These functions are called repeatedly, updating the motor object
    int updateSlewRate(int targetSpeed); // Doesn't work
    void move(); // Applies the current speed to the motor
    static void periodicUpdate(); // Updates all motors. Calls the move function on all motors

    static void resetEncoders();
};

#endif
