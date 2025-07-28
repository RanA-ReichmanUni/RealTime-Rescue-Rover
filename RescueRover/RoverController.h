#pragma once

#include "ObstacleAvoidance.h"
#include "MovementManager.h"
#include "MotorDriver.h"  
#include <memory>
#include <optional>
#include <stack>

// Default duration for each movement step
static constexpr int DefaultStepDurationMs = 1000;

struct AlternativePath {
    int stepIndex;
    MoveDecision alternative;
	// Constructor to initialize AlternativePath with step index and alternative decision
    AlternativePath(int stepIndex, MoveDecision alternative)
        : stepIndex(stepIndex), alternative(alternative) {
    }
};

class RoverController {
public:
    RoverController(std::unique_ptr<ObstacleAvoidance> obstacleAvoidance,
        std::unique_ptr<MovementManager> movementManager,
        std::unique_ptr<MotorDriver> motorDriver,
        int forwardSpeed,
        int turnSpeed);

    void moveStep();    // Core decision + move execution
    void timeTravel();  // Reverse to alternative path

private:
    std::unique_ptr<ObstacleAvoidance> obstacleAvoidance;
    std::unique_ptr<MovementManager> movementManager;
    std::unique_ptr<MotorDriver> motorDriver;
    int forwardSpeed;
    int turnSpeed;

    std::vector<MoveDecision> movementHistory;
    std::stack<AlternativePath> alternativePaths;

    SensorStatus readSensorData();
    bool isStuck(MoveDecision decision) const;
};
