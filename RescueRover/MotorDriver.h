#pragma once


class MotorDriver {
public:
    MotorDriver(int leftPwmPin, int leftDirPin,
        int rightPwmPin, int rightDirPin);

    void setSpeeds(int leftSpeed, int rightSpeed);  // Positive = forward, Negative = reverse
    void stop();

private:
    int leftPwmPin;
    int leftDirPin;
    int rightPwmPin;
    int rightDirPin;

    void applyMotorSpeed(int pwmPin, int dirPin, int speed);
};
