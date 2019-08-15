#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <avr/pgmspace.h>

#include "engine.h"
#include "move.h"
#include "spriteData.h"

void moveFunction5B() {
    if (getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active) {
        ++player.x;
    }
}

const Move MOVE_5A = {
    startupFrames: 6,
    activeFrames: 3,
    recoveryFrames: 12,
    hitstunFrames: 24,
    damage: 50,
    startupSprite: PLAYER_5A_STARTUP,
    activeSprite: PLAYER_5A_ACTIVE,
    recoverySprite: PLAYER_5A_RECOVERY,
    moveFunction: nullptr,
    hitboxData: ConstHitbox {
        xOffset: 8,
        yOffset: 0,
        width: 8,
        height: 16
    }
};

const Move MOVE_5B = {
    startupFrames: 12,
    activeFrames: 6,
    recoveryFrames: 20,
    hitstunFrames: 30,
    damage: 100,
    startupSprite: PLAYER_5B_STARTUP,
    activeSprite: PLAYER_5B_ACTIVE,
    recoverySprite: PLAYER_5B_RECOVERY,
    moveFunction: moveFunction5B,
    hitboxData: ConstHitbox {
        xOffset: 8,
        yOffset: 0,
        width: 14,
        height: 16
    }
};

const Move MOVE_2A = {
    startupFrames: 7,
    activeFrames: 2,
    recoveryFrames: 11,
    hitstunFrames: 20,
    damage: 50,
    startupSprite: PLAYER_2A_STARTUP,
    activeSprite: PLAYER_2A_ACTIVE,
    recoverySprite: PLAYER_2A_RECOVERY,
    moveFunction: nullptr,
    hitboxData: ConstHitbox {
        xOffset: 12,
        yOffset: 17,
        width: 4,
        height: 7
    }
};

#endif

/*
// Copy and paste base for convenience:

const Move MOVE_ = {
    startupFrames: ,
    activeFrames: ,
    recoveryFrames: ,
    hitstunFrames: ,
    damage: ,
    startupSprite: PLAYER__STARTUP,
    activeSprite: PLAYER__ACTIVE,
    recoverySprite: PLAYER__RECOVERY,
    hitboxData: ConstHitbox {
        xOffset: ,
        yOffset: ,
        width: ,
        height: 
    }
};

*/