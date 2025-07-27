#include "MovementManager.h"

MovementManager::MovementManager(int turnDurationMs, int forwardDurationMs,
    int forwardSpeed, int turnSpeed)
    : turnDurationMs(turnDurationMs),
    forwardDurationMs(forwardDurationMs),
    forwardSpeed(forwardSpeed),
    turnSpeed(turnSpeed) {
}


std::vector<MovementStep> MovementManager::planSideBypass(BypassDirection direction) {
    std::vector<MovementStep> steps;

    if (direction == BypassDirection::Left) {
        steps.push_back({ MotorAction::TurnLeft, turnDurationMs });
        steps.push_back({ MotorAction::Forward, forwardDurationMs });
        steps.push_back({ MotorAction::TurnRight, turnDurationMs });
    }
    else {
        steps.push_back({ MotorAction::TurnRight, turnDurationMs });
        steps.push_back({ MotorAction::Forward, forwardDurationMs });
        steps.push_back({ MotorAction::TurnLeft, turnDurationMs });
    }

    return steps;
}
