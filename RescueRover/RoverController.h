#pragma once

#include "ObstacleAvoidance.h"
#include "MovementManager.h"
#include "MotorDriver.h"  
#include <memory>


static constexpr int DefaultStepDurationMs = 1000; // Default step duration in milliseconds

enum class BypassDirection {
    Left,
    Right
};

class RoverController {
public:
    RoverController(std::unique_ptr<ObstacleAvoidance> obstacleAvoidance,
        std::unique_ptr<MovementManager> movementManager,
        std::unique_ptr<MotorDriver> motorDriver,
        int forwardSpeed,
        int turnSpeed);

    void moveStep();  // Core movement logic

private:
    std::unique_ptr<ObstacleAvoidance> obstacleAvoidance;
    std::unique_ptr<MovementManager> movementManager;
    std::unique_ptr<MotorDriver> motorDriver;
    int forwardSpeed;
    int turnSpeed;

    // Internal helpers
    SensorStatus readSensorData();  // Simulated for now
    void sendMotorCommand(const MovementStep& step);
    bool isStuck(MoveDecision decision) const;
};
