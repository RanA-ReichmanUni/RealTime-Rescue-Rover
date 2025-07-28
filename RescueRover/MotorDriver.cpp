#include "MotorDriver.h"
#include <algorithm> 
#include <iostream>

// ToDo - Replace with motor control functions 

MotorDriver::MotorDriver(int leftPwmPin, int leftDirPin,
    int rightPwmPin, int rightDirPin)
    : leftPwmPin(leftPwmPin),
    leftDirPin(leftDirPin),
    rightPwmPin(rightPwmPin),
    rightDirPin(rightDirPin) {
   
}

void MotorDriver::setSpeeds(int leftSpeed, int rightSpeed) {
    applyMotorSpeed(leftPwmPin, leftDirPin, leftSpeed);
    applyMotorSpeed(rightPwmPin, rightDirPin, rightSpeed);
}

void MotorDriver::stop() {
    applyMotorSpeed(leftPwmPin, leftDirPin, 0);
    applyMotorSpeed(rightPwmPin, rightDirPin, 0);
}

void MotorDriver::applyMotorSpeed(int pwmPin, int dirPin, int speed) {
    bool forward = speed >= 0;
    int magnitude = std::min(std::abs(speed), 255);  // clamp to max PWM

    // Todo - Replace with actual pin writes 
    std::cout << "PWM Pin " << pwmPin
        << " set to " << magnitude
        << " (" << (forward ? "Forward" : "Reverse") << ")\n";
}
