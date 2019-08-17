#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>

#include "hitbox.h"
#include "move.h"

#define CROUCH_FRAME_LIMIT 4

enum class PlayerState { Idle, Walking, Dashing, ExecutingMove };
enum class PlayerCrouchState { Standing, InBetween, Crouching, };

typedef struct Player {
    uint8_t x;
    uint8_t y;
    int8_t xOffset;
    int8_t yOffset;
    Move const *currentMove;
    uint8_t currentMoveFrameCounter;
    PlayerState state;
    uint8_t crouchFrame;
    PlayerCrouchState crouchState;
    uint8_t const *sprite;
    Hitbox hitbox;
    bool currentMoveHit; // TODO: Replace this with a solution that supports with slow fireballs. Those will require their own bool or something else.
} Player;

void playerSetIdle(Player *player);
void playerExecuteMove(Player *player, Move const *move);

PlayerCrouchState getPlayerCrouchState(Player *player, uint8_t input);

#endif