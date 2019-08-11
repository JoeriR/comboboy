#ifndef PLAYER_C
#define PLAYER_C

#include "input.h"
#include "player.h"
#include "spriteData.h"

#define CROUCH_FRAME_LIMIT 4

// crouchFrame decides the PlayerCrouchState that we're in
uint8_t crouchFrame = 0;

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

PlayerCrouchState getPlayerCrouchState(Player *player, uint8_t input) {
    if (input & CB_DOWN_BUTTON && player->state == PlayerState::Idle && crouchFrame < CROUCH_FRAME_LIMIT)
        ++crouchFrame;

    if (!(input & CB_DOWN_BUTTON)) {
        if (crouchFrame > 0)
            --crouchFrame;
    }

    if (crouchFrame == 0)
        return PlayerCrouchState::Standing;
    else if (crouchFrame == CROUCH_FRAME_LIMIT)
        return PlayerCrouchState::Crouching;
    else
        return PlayerCrouchState::InBetween;
}

#endif