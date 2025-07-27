#pragma once
#include <vector>
#include "RoverController.h"  // to use BypassDirection

enum class MotorAction {
    Forward,
    TurnLeft,
    TurnRight,
    Reverse,
    STOP,
};


struct MovementStep {
    MotorAction type;
    int durationMs;
};

class MovementManager {
public:

    MovementManager(int turnDurationMs, int forwardDurationMs, int forwardSpeed, int turnSpeed);
    std::vector<MovementStep> planSideBypass(BypassDirection side);

private:

    int turnDurationMs;
    int forwardDurationMs;
    int forwardSpeed;
    int turnSpeed;
};
