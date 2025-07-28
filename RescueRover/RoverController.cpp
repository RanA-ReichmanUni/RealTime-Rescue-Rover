#include "RoverController.h"
#include <iostream>
#include "Utils.h"
#include <thread>
// Constructor definition
// -----------------------
// The colon (:) introduces the initializer list — a special C++ feature that allows
// us to directly initialize member variables before the constructor body runs.
//It tells the compiler to initialize `obstacleAvoidance` member with the provided unique_ptr (named oa).

// This constructor receives a unique_ptr to an ObstacleAvoidance object.
// Since std::unique_ptr cannot be copied, we use std::move() to transfer ownership
// into the class member (obstacleAvoidance, with lead small letter) variable.

RoverController::RoverController(std::unique_ptr<ObstacleAvoidance> oa,
    std::unique_ptr<MovementManager> mm,
    std::unique_ptr<MotorDriver> md,
    int fSpeed,
    int tSpeed)
    : obstacleAvoidance(std::move(oa)),
    movementManager(std::move(mm)),
    motorDriver(std::move(md)),
    forwardSpeed(fSpeed),
    turnSpeed(tSpeed) {}   //Embpty constructor body, 
                                            //since all initialization is done in the initializer list.



void RoverController::moveStep() {
    SensorStatus sensors = readSensorData();
    MoveDecision decision = obstacleAvoidance->decide(sensors);

    if (isStuck(decision)) {
        std::cout << "[Controller] STUCK detected — moveStep did not issue command.\n";
        return;
    }
	else {// Anything but STUCK is a valid motor action
        MotorAction action = Utils::decisionToMotorAction(decision);
		MovementStep step = { action, DefaultStepDurationMs }; // 1000 ms duration for each step

        sendMotorCommand(step);
    }
    
}


SensorStatus RoverController::readSensorData() {
    // Simulated distances — Todo - replace with real sensor reading
    SensorStatus sensors;
    std::cout << "Enter front distance (cm): ";
    std::cin >> sensors.frontClearDistance;
    std::cout << "Enter left distance (cm): ";
    std::cin >> sensors.leftClearDistance;
    std::cout << "Enter right distance (cm): ";
    std::cin >> sensors.rightClearDistance;
    return sensors;
}

void RoverController::sendMotorCommand(const MovementStep& step) {
    int leftSpeed = 0;
    int rightSpeed = 0;

    switch (step.type) {
    case MotorAction::Forward:
        leftSpeed = forwardSpeed;
        rightSpeed = forwardSpeed;
        break;

    case MotorAction::TurnLeft:
        leftSpeed = -turnSpeed;
        rightSpeed = turnSpeed;
        break;

    case MotorAction::TurnRight:
        leftSpeed = turnSpeed;
        rightSpeed = -turnSpeed;
        break;
    }

    // Launch a thread to execute the motor command
    std::thread motorThread([this, leftSpeed, rightSpeed, step]() {
        motorDriver->setSpeeds(leftSpeed, rightSpeed);
        std::this_thread::sleep_for(std::chrono::milliseconds(step.durationMs)); // Non-blocking delay
        motorDriver->stop();
        });

    // Detach the thread to allow it to run independently
    motorThread.detach();
}

bool RoverController::isStuck(MoveDecision decision) const {
    return decision == MoveDecision::STUCK;
}
