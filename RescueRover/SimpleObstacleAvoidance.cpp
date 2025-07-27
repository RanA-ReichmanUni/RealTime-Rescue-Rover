#include "SimpleObstacleAvoidance.h"

constexpr double FRONT_CLEARANCE_THRESHOLD = 30.0;  // cm: distance considered "safe" for forward movement
constexpr double SIDE_CLEARANCE_THRESHOLD = 10.0;  // cm: minimum distance required for side movement

MoveDecision SimpleObstacleAvoidance::decide(const SensorStatus& sensors) {
    // Prefer forward movement if there's enough space ahead
    if (sensors.frontClearDistance >= FRONT_CLEARANCE_THRESHOLD)
        return MoveDecision::FORWARD;

    // Otherwise, evaluate side options
    bool leftUsable = sensors.leftClearDistance >= SIDE_CLEARANCE_THRESHOLD;
    bool rightUsable = sensors.rightClearDistance >= SIDE_CLEARANCE_THRESHOLD;

    if (leftUsable && rightUsable) {
        // Prefer the side with more space
        return (sensors.leftClearDistance > sensors.rightClearDistance)
            ? MoveDecision::LEFT
            : MoveDecision::RIGHT;
    }

    if (leftUsable)  return MoveDecision::LEFT;
    if (rightUsable) return MoveDecision::RIGHT;

    // All directions are too tight: declare stuck
    if (sensors.frontClearDistance < SIDE_CLEARANCE_THRESHOLD &&
        sensors.leftClearDistance < SIDE_CLEARANCE_THRESHOLD &&
        sensors.rightClearDistance < SIDE_CLEARANCE_THRESHOLD) {
        return MoveDecision::STUCK;
    }

    // Fallback to reverse if forward is blocked and no side is usable
	//----- Placeholder for reverse timeTravel logic -----
    return MoveDecision::REVERSE;
}
