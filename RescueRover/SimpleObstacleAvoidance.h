#pragma once
#include "ObstacleAvoidance.h"

// A basic obstacle avoidance module that uses distance thresholds
// to decide the safest direction to move.
class SimpleObstacleAvoidance : public ObstacleAvoidance {
public:
    MoveDecision decide(const SensorStatus& sensors) override;
};
