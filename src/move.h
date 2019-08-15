#ifndef MOVE_H
#define MOVE_H

#include <Arduino.h>

#include "hitbox.h"


enum class MoveState { Startup, Active, Recovery, Finished };

typedef struct Move {
    const uint8_t startupFrames;
    const uint8_t activeFrames;
    const uint8_t recoveryFrames;
    const uint8_t hitstunFrames;
    const uint8_t damage;
    const uint8_t *startupSprite;
    const uint8_t *activeSprite;
    const uint8_t *recoverySprite;
    void(*moveFunction)();
    const ConstHitbox hitboxData;
} Move;

MoveState getMoveState(Move const *move, uint8_t currentFrame);

#endif