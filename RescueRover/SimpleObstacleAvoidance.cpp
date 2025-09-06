#include "SimpleObstacleAvoidance.h"

constexpr double FRONT_CLEARANCE_THRESHOLD = 30.0;  // cm: distance considered "safe" for forward movement
constexpr double SIDE_CLEARANCE_THRESHOLD = 10.0;  // cm: minimum distance required for side movement



// This function analyzes sensor data to determine the best movement direction
// based on available space in front and to the sides.
// It returns a DecisionResult indicating the chosen direction and any alternative.

DecisionResult SimpleObstacleAvoidance::decide(const SensorStatus& sensors) {




    DecisionResult result{};

    // Prefer forward movement if there's enough space ahead
    if (sensors.frontClearDistance >= FRONT_CLEARANCE_THRESHOLD) {
        result.chosen = MoveDecision::FORWARD;
        return result;
    }

    // Otherwise, evaluate side options
    bool leftUsable = sensors.leftClearDistance >= SIDE_CLEARANCE_THRESHOLD;
    bool rightUsable = sensors.rightClearDistance >= SIDE_CLEARANCE_THRESHOLD;

    if (leftUsable && rightUsable) {
        // Prefer the side with more space
        if (sensors.leftClearDistance > sensors.rightClearDistance) {
            result.chosen = MoveDecision::LEFT;
            result.alternative = MoveDecision::RIGHT; // store alternative
        }
        else {
            result.chosen = MoveDecision::RIGHT;
            result.alternative = MoveDecision::LEFT;  // store alternative
        }
        return result;
    }

    if (leftUsable) {
        result.chosen = MoveDecision::LEFT;
        return result;
    }
    if (rightUsable) {
        result.chosen = MoveDecision::RIGHT;
        return result;
    }

    // All directions are too tight: declare stuck
    if (sensors.frontClearDistance < SIDE_CLEARANCE_THRESHOLD &&
        sensors.leftClearDistance < SIDE_CLEARANCE_THRESHOLD &&
        sensors.rightClearDistance < SIDE_CLEARANCE_THRESHOLD) {
        result.chosen = MoveDecision::STUCK;
        return result;
    }

    // Fallback to reverse if forward is blocked and no side is usable
    // ----- Placeholder for reverse timeTravel logic -----
    result.chosen = MoveDecision::REVERSE;
    return result;
}
