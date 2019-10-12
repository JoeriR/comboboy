#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>

#include "hitbox.h"
#include "move.h"

#define CROUCH_FRAME_LIMIT 4

#define WALK_1_FRAMES 4
#define WALK_2_FRAMES 4

enum class PlayerState { Idle, Dashing, ExecutingMove };
enum class PlayerCrouchState { Standing, InBetween, Crouching, };
enum class PlayerWalkState { Standing, Walk1, Walk2 };

typedef struct Player {
    uint8_t x;
    uint8_t y;
    int8_t xOffset;
    int8_t yOffset;
    Move const *currentMove;
    uint8_t currentMoveFrameCounter;
    PlayerState state;
    uint8_t crouchFrame;
    uint8_t walkFrame;
    PlayerCrouchState crouchState;
    uint8_t const *sprite;
    Hitbox hitbox;
    bool currentMoveHit;
} Player;

void playerSetIdle(Player *player);
void playerExecuteMove(Player *player, Move const *move);

PlayerCrouchState getPlayerCrouchState(Player *player, uint8_t input);
PlayerWalkState updatePlayerWalkFrame(Player *player);

#endif