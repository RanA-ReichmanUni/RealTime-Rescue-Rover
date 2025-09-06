#include "RoverController.h"
#include <iostream>
#include "Utils.h"
#include <thread>

RoverController::RoverController(std::unique_ptr<ObstacleAvoidance> oa,
    std::unique_ptr<MovementManager> mm,
    std::unique_ptr<MotorDriver> md,
    int fSpeed,
    int tSpeed)
    : obstacleAvoidance(std::move(oa)),
    movementManager(std::move(mm)),
    motorDriver(std::move(md)),
    forwardSpeed(fSpeed),
    turnSpeed(tSpeed) {
}

void RoverController::moveStep() {
    SensorStatus sensors = readSensorData();
    DecisionResult decision = obstacleAvoidance->decide(sensors);

    if (isStuck(decision.chosen)) {
        std::cout << "[Controller] STUCK detected — considering timeTravel.\n";
        timeTravel();
        return;
    }

    // Store alternative path if OA detected one
    if (decision.alternative.has_value()) {
        alternativePaths.push({ movementHistory.size(), decision.alternative.value() });
    }

    // Execute move via MovementManager
    movementManager->executeMove(decision);

    // Log executed move
    movementHistory.push_back(decision.chosen);
}

SensorStatus RoverController::readSensorData() {
    SensorStatus sensors;
    std::cout << "Enter front distance (cm): ";
    std::cin >> sensors.frontClearDistance;
    std::cout << "Enter left distance (cm): ";
    std::cin >> sensors.leftClearDistance;
    std::cout << "Enter right distance (cm): ";
    std::cin >> sensors.rightClearDistance;
    return sensors;
}

bool RoverController::isStuck(MoveDecision decision) const {
    return decision == MoveDecision::STUCK;
}

void RoverController::timeTravel() {
    if (alternativePaths.empty()) {
        std::cout << "[Controller] No alternative paths to time travel.\n";
        return;
    }

    AlternativePath alt = alternativePaths.top();
    alternativePaths.pop();

    // Reverse back to the crossroad step index
    while ((int)movementHistory.size() > alt.stepIndex) {
        movementManager->executeInReverseOrder(movementHistory.back());
        movementHistory.pop_back();
    }

    // Take alternative path

    movementManager->executeMove(alt.alternative);
    movementHistory.push_back(alt.alternative);
}
