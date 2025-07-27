#pragma once

enum class MoveDecision {
    FORWARD,
    LEFT,
    RIGHT,
    REVERSE,
    STUCK  // no good option
};


struct SensorStatus {
    double frontClearDistance;
    double leftClearDistance;
    double rightClearDistance;
    // Add more (e.g., distances) if needed
};

class ObstacleAvoidance {
public:
    virtual ~ObstacleAvoidance() = default;
    virtual MoveDecision decide(const SensorStatus& sensors) = 0;
};

