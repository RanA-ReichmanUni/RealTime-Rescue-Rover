#include "Utils.h"
#include <stdexcept>

namespace Utils {
    MotorAction decisionToMotorAction(MoveDecision decision) {
        switch (decision) {
        case MoveDecision::FORWARD:
            return MotorAction::Forward;
        case MoveDecision::LEFT:
            return MotorAction::TurnLeft;
        case MoveDecision::RIGHT:
            return MotorAction::TurnRight;
        default:
            throw std::invalid_argument("Unsupported MoveDecision value");
        }
    }
}