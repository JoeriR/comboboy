#ifndef MOVE_C
#define MOVE_C

#include "move.h"

MoveState getMoveState(Move *move, uint8_t currentFrame) {
    if (currentFrame < move->startupFrames)
        return MoveState::Startup;
    else if (currentFrame < move->startupFrames + move->activeFrames)
        return MoveState::Active;
    else if (currentFrame < move->startupFrames + move->activeFrames + move->recoveryFrames)
        return MoveState::Recovery;
    else
        return MoveState::Finished;
}

#endif