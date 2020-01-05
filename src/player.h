#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>

#include "hitbox.h"
#include "move.h"

#define PLAYER_HITBOX_X_OFFSET 3
#define PLAYER_HITBOX_Y_OFFSET 5

#define CROUCH_FRAME_LIMIT 4

#define WALK_1_FRAMES 4
#define WALK_2_FRAMES 4

#define JUMP_STARTUP_FRAMES 4
#define JUMP_ASCENDING_FRAMES 18
#define JUMP_FLOATING_FRAMES 20

enum class PlayerState { Idle, Dashing, ExecutingMove };
enum class PlayerCrouchState { Standing, InBetween, Crouching };
enum class PlayerWalkState { Standing, Walk1, Walk2 };
enum class PlayerJumpState { Standing, Startup, Ascending, Floating, Falling };

typedef struct Player {
    uint8_t x;
    uint8_t y;
    int8_t xOffset;
    int8_t yOffset;
    uint8_t direction;
    Move const *currentMove;
    uint8_t currentMoveFrameCounter;
    PlayerState state;
    uint8_t crouchFrame;
    uint8_t walkFrame;
    uint8_t jumpFrame;
    int8_t jumpDirection;   // 0 for neutral jump, 1 or -1 for directional jumps
    PlayerCrouchState crouchState;
    uint8_t const *sprite;
    Hitbox hitbox;
    bool currentMoveHit;
} Player;

void playerSetIdle(Player *player);
void playerExecuteMove(Player *player, Move const *move);

void playerMoveForwards(Player *player, uint8_t pixelsForward);

void playerMoveBackwards(Player *player, uint8_t pixelsBackward);

void playerSyncPositionToHitbox(Player *player);

PlayerCrouchState getPlayerCrouchState(Player *player, uint8_t input);
PlayerWalkState updatePlayerWalkFrame(Player *player);
PlayerJumpState updatePlayerJumpFrame(Player *player);

#endif