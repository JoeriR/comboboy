#ifndef PLAYER_C
#define PLAYER_C

#include "input.h"
#include "player.h"
#include "spriteData.h"


void playerSetIdle(Player *player) {
    player->currentMove = nullptr;
    player->currentMoveFrameCounter = 0;
    player->state = PlayerState::Idle;
    player->sprite = PLAYER_IDLE;
}

void playerExecuteMove(Player *player, Move const *move) {
    player->currentMove = move;
    player->currentMoveFrameCounter = 0;
    player->currentMoveHit = false; // CARE:
    player->state = PlayerState::ExecutingMove;
}

// crouchFrame decides the PlayerCrouchState that we're in
PlayerCrouchState getPlayerCrouchState(Player *player, uint8_t input) {
    if (input & CB_DOWN_BUTTON && player->state == PlayerState::Idle && player->crouchFrame < CROUCH_FRAME_LIMIT)
        ++player->crouchFrame;

    if (!(input & CB_DOWN_BUTTON)) {
        if (player->crouchFrame > 0)
            --player->crouchFrame;
    }

    if (player->crouchFrame == 0)
        return PlayerCrouchState::Standing;
    else if (player->crouchFrame == CROUCH_FRAME_LIMIT)
        return PlayerCrouchState::Crouching;
    else
        return PlayerCrouchState::InBetween;
}

PlayerWalkState updatePlayerWalkFrame(Player *player) {
    ++player->walkFrame;

    if (player->walkFrame > WALK_1_FRAMES + WALK_2_FRAMES)
        player->walkFrame = 0;

    if (player->walkFrame < WALK_1_FRAMES) 
        return PlayerWalkState::Walk1;
    else
        return PlayerWalkState::Walk2;
}

#endif