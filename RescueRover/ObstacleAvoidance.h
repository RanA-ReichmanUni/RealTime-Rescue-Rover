#pragma once
#include <optional> // Ensure this include is present

enum class MoveDecision {
    FORWARD,
    LEFT,
    RIGHT,
    REVERSE,
    STUCK  // no good option
};
enum class BypassDirection {
    Left,
    Right
};

struct DecisionResult {
    MoveDecision chosen;                              // What OA decided
    bool isBypass = false;                            // True if this is a side bypass
    std::optional<BypassDirection> bypassDirection;   // Direction of bypass if applicable
    std::optional<MoveDecision> alternative;          // Alternative path if one exists
};

struct SensorStatus {
    double frontClearDistance;
    double leftClearDistance;
    double rightClearDistance;
    
};

class ObstacleAvoidance {
public:
    virtual ~ObstacleAvoidance() = default;
    virtual DecisionResult decide(const SensorStatus& sensors) = 0;
};
