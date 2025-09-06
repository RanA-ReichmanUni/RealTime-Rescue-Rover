#include "MovementManager.h"
#include <thread>
#include <chrono>

MovementManager::MovementManager(std::unique_ptr<MotorDriver> md,
    int turnDurationMs,
    int forwardDurationMs,
    int forwardSpeed,
    int turnSpeed)
    : motorDriver(std::move(md)),
    turnDurationMs(turnDurationMs),
    forwardDurationMs(forwardDurationMs),
    forwardSpeed(forwardSpeed),
    turnSpeed(turnSpeed) {
}

// Execute single MoveDecision Delegator
void MovementManager::executeMove(DecisionResult decision) {

    if (decision.isBypass && decision.bypassDirection.has_value()) {
        executeSteps(planSideBypass(decision.bypassDirection.value()));
    }
    else {
        executeMove(decision.chosen);  // executeMove() - MoveDecision parameter overload 
                                       //..for single step commands.
    }
}

// Execute single MoveDecision
void MovementManager::executeMove(MoveDecision decision) {
    MotorAction action;
    int duration = forwardDurationMs;


    switch (decision) {
    case MoveDecision::FORWARD:
        action = MotorAction::Forward;
        duration = forwardDurationMs;
        break;
    case MoveDecision::LEFT:
        action = MotorAction::TurnLeft;
        duration = turnDurationMs;
        break;
    case MoveDecision::RIGHT:
        action = MotorAction::TurnRight;
        duration = turnDurationMs;
        break;
    case MoveDecision::REVERSE:
        action = MotorAction::Reverse;
        duration = forwardDurationMs; // Reverse is similar to forward
        break;
    default:
        action = MotorAction::STOP;
        duration = 0;
        break;
    }
    
    executeSteps({ {action, duration} });
}

// Execute reverse move (for timeTravel)
void MovementManager::executeInReverseOrder(MoveDecision decision) {
    MotorAction reverseAction;
    int duration = forwardDurationMs;

    switch (decision) {
    case MoveDecision::FORWARD:
        reverseAction = MotorAction::Reverse;
        duration = forwardDurationMs;
        break;
    case MoveDecision::LEFT:
        reverseAction = MotorAction::TurnRight;
        duration = turnDurationMs;
        break;
    case MoveDecision::RIGHT:
        reverseAction = MotorAction::TurnLeft;
        duration = turnDurationMs;
        break;
    case MoveDecision::REVERSE:
        reverseAction = MotorAction::Forward;
        duration = forwardDurationMs;
        break;
    default:
        reverseAction = MotorAction::STOP;
        duration = 0;
        break;
    }

    executeSteps({ {reverseAction, duration} });
}

// Execute a sequence of steps
void MovementManager::executeSteps(const std::vector<MovementStep>& steps) {
    for (const auto& step : steps) {
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
        case MotorAction::Reverse:
            leftSpeed = -forwardSpeed;
            rightSpeed = -forwardSpeed;
            break;
        case MotorAction::STOP:
            motorDriver->stop();
            continue;
        }

        motorDriver->setSpeeds(leftSpeed, rightSpeed);
        std::this_thread::sleep_for(std::chrono::milliseconds(step.durationMs));
        motorDriver->stop();
    }
}

// Plan bypass steps
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
