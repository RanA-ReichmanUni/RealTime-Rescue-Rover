#pragma once
#include "MovementManager.h"
#include "ObstacleAvoidance.h"

namespace Utils {
    MotorAction decisionToMotorAction(MoveDecision decision);
}