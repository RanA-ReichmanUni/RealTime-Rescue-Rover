// RescueRover.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include "RoverController.h"
#include "ObstacleAvoidance.h"
#include "SimpleObstacleAvoidance.h"
#include "MovementManager.h"
#include "MotorDriver.h"

// Mock ObstacleAvoidance for testing - returns preprogrammed decisions
class TestObstacleAvoidance : public ObstacleAvoidance {
private:
    std::vector<DecisionResult> testSequence;
    size_t stepIndex = 0;

public:
    TestObstacleAvoidance() {
        // Create a test sequence of movements
        testSequence.push_back({MoveDecision::FORWARD, false, {}, {}});
        testSequence.push_back({MoveDecision::LEFT, false, {}, {}});
        testSequence.push_back({MoveDecision::FORWARD, false, {}, {}});
        testSequence.push_back({MoveDecision::RIGHT, false, {}, {}});
        testSequence.push_back({MoveDecision::FORWARD, false, {}, {}});
    }

    DecisionResult decide(const SensorStatus& sensors) override {
        std::cout << "[TestObstacleAvoidance] Front: " << sensors.frontClearDistance 
                  << " cm, Left: " << sensors.leftClearDistance 
                  << " cm, Right: " << sensors.rightClearDistance << " cm\n";
        
        if (stepIndex >= testSequence.size()) {
            stepIndex = 0;  // Loop back to start
        }
        
        DecisionResult result = testSequence[stepIndex];
        stepIndex++;
        return result;
    }
};

int main()
{
    std::cout << "=== RescueRover Test Harness ===\n";
    std::cout << "Testing core control flow with mock sensor data\n\n";

    // Prepare mock sensor input data
    // Each line contains: front distance, left distance, right distance
    std::string mockSensorInput = 
        "50 40 35\n"     // Step 1: clear path ahead
        "20 45 30\n"     // Step 2: obstacle ahead, left is better
        "55 40 38\n"     // Step 3: clear ahead again
        "25 30 50\n"     // Step 4: obstacle ahead, right is better
        "60 42 40\n";    // Step 5: clear path ahead
    
    // Redirect cin to use our mock input
    std::istringstream mockInput(mockSensorInput);
    std::cin.rdbuf(mockInput.rdbuf());

    // Create components
    auto motorDriver = std::make_unique<MotorDriver>(1, 2, 3, 4);
    auto movementManager = std::make_unique<MovementManager>(
        std::make_unique<MotorDriver>(1, 2, 3, 4),
        500,    // turnDurationMs
        1000,   // forwardDurationMs
        255,    // forwardSpeed
        180     // turnSpeed
    );
    auto obstacleAvoidance = std::make_unique<TestObstacleAvoidance>();

    // Create RoverController
    RoverController controller(
        std::move(obstacleAvoidance),
        std::move(movementManager),
        std::move(motorDriver),
        255,    // forwardSpeed
        180     // turnSpeed
    );

    // Run test cycles
    std::cout << "Running 5 movement steps with mock sensor data:\n";
    std::cout << "============================================\n\n";
    
    for (int i = 0; i < 5; i++) {
        std::cout << "STEP " << (i + 1) << ":\n";
        std::cout << "--------\n";
        controller.moveStep();
        std::cout << "\n";
    }

    std::cout << "============================================\n";
    std::cout << "Test Complete - All steps executed successfully!\n";
    return 0;
}

