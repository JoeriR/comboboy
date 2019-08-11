#ifndef PLAYER_C
#define PLAYER_C

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

#endif