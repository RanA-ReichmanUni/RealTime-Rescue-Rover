#pragma once
#include <vector>
#include <memory>
#include "MotorDriver.h"
#include "ObstacleAvoidance.h"  // For BypassDirection, MoveDecision

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
    MovementManager(std::unique_ptr<MotorDriver> motorDriver,
        int turnDurationMs,
        int forwardDurationMs,
        int forwardSpeed,
        int turnSpeed);

    // Execute a single movement decision
    void executeMove(DecisionResult decision);

    // Execute a single movement decision
    void executeMove(MoveDecision decision);

    // Execute a reverse movement decision (for timeTravel)
    void executeInReverseOrder(MoveDecision decision);

    // Execute a series of steps (used by OA bypass)
    void executeSteps(const std::vector<MovementStep>& steps);

    // Plan bypass sequence
    std::vector<MovementStep> planSideBypass(BypassDirection side);

private:
    std::unique_ptr<MotorDriver> motorDriver;
    int turnDurationMs;
    int forwardDurationMs;
    int forwardSpeed;
    int turnSpeed;
};
