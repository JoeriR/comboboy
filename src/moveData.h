#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <avr/pgmspace.h>

#include "engine.h"
#include "knockback.h"
#include "knockbackData.h"
#include "move.h"
#include "projectile.h"
#include "spriteData.h"

// Move Functions
void moveFunction5B() {
    if (getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active) {
        playerMoveForwards(&player, 1);
        player.xOffset = -4;
    }
}

void moveFunction2B() {
    if (getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Startup && player.currentMoveFrameCounter % 3 == 0) 
        playerMoveForwards(&player, 1);
    if (getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active) 
        playerMoveForwards(&player, 2);
    if (getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Recovery && player.currentMoveFrameCounter % 2 == 0) 
        playerMoveForwards(&player, 1);
}

void moveFunction236A() {
    if (!isProjectileOnScreen(fireballPtr) && getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Recovery && player.currentMoveFrameCounter == player.currentMove->startupFrames + player.currentMove->activeFrames + 1) {
        fireballPtr->x = player.x;
        fireballPtr->y = player.y;
        fireballPtr->damage = 12;
        fireballPtr->direction = player.direction;
        fireballPtr->despawnAfterHitstop = false;
    }
}

void moveFunctionHandstandKick() {
    if (getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active) {
        playerMoveForwards(&player, 1);
        player.y -= 2;
        player.jumpFrame = JUMP_ASCENDING_FRAMES + 1;   // Put and keep the player in an airborne state
    }
    if (getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Recovery && player.currentMoveFrameCounter % 4) {
        playerMoveForwards(&player, 1);
        player.y -= 1;

        // Handle air movement after this move has been finished
        player.jumpFrame = JUMP_ASCENDING_FRAMES + 5;

        // Set jump direction
        if (player.direction)
            player.jumpDirection = 1;
        else 
            player.jumpDirection = -1;
    }
        
}

// Move Data
const Move MOVE_5A = {
    startupFrames: 6,
    activeFrames: 3,
    recoveryFrames: 12,
    hitstunFrames: 24,
    damage: 5,
    startupSprite: PLAYER_5A_STARTUP,
    activeSprite: PLAYER_5A_ACTIVE,
    recoverySprite: PLAYER_5A_RECOVERY,
    moveFunction: nullptr,
    knockback: &knockback_weak,
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
    damage: 10,
    startupSprite: PLAYER_5B_STARTUP,
    activeSprite: PLAYER_5B_ACTIVE,
    recoverySprite: PLAYER_5B_RECOVERY,
    moveFunction: moveFunction5B,
    knockback: &knockback_5B,
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
    damage: 5,
    startupSprite: PLAYER_2A_STARTUP,
    activeSprite: PLAYER_2A_ACTIVE,
    recoverySprite: PLAYER_2A_RECOVERY,
    moveFunction: nullptr,
    knockback: &knockback_weak,
    hitboxData: ConstHitbox {
        xOffset: 12,
        yOffset: 17,
        width: 4,
        height: 7
    }
};

const Move MOVE_2B = {
    startupFrames: 10,
    activeFrames: 8,
    recoveryFrames: 20,
    hitstunFrames: 32,
    damage: 10,
    startupSprite: PLAYER_2B_STARTUP,
    activeSprite: PLAYER_2B_ACTIVE,
    recoverySprite: PLAYER_2B_RECOVERY,
    moveFunction: moveFunction2B,
    knockback: &knockback_2B,
    hitboxData: ConstHitbox {
        xOffset: 6,
        yOffset: 11,
        width: 13,
        height: 13
    }
};

const Move MOVE_236A = {
    startupFrames: 15,
    activeFrames: 2,
    recoveryFrames: 20,
    hitstunFrames: 45,
    damage: 12,
    startupSprite: PLAYER_236A_STARTUP,
    activeSprite: PLAYER_236A_ACTIVE,
    recoverySprite: PLAYER_236A_RECOVERY,
    moveFunction: moveFunction236A,
    knockback: &knockback_236A_fireball,    // Knockback is triggered when the fireball hits the dummy
    hitboxData: ConstHitbox {   // 236A launches a fireball that caries a hitbox, the move itself does not
        xOffset: 0,
        yOffset: 0,
        width: 0,
        height: 0
    }
};


const Move MOVE_HANDSTAND_KICK = {
    startupFrames: 10,
    activeFrames: 8,
    recoveryFrames: 24,
    hitstunFrames: 45,
    damage: 12,
    startupSprite: PLAYER_HANDSTAND_KICK_STARTUP,
    activeSprite: PLAYER_HANDSTAND_KICK_ACTIVE,
    recoverySprite: PLAYER_HANDSTAND_KICK_RECOVERY,
    moveFunction: moveFunctionHandstandKick,
    knockback: &knockback_2B,
    hitboxData: ConstHitbox {
        xOffset: 0,
        yOffset: 0,
        width: 20,
        height: 28
    }
};

const Move MOVE_J_5A = {
    startupFrames: 6,
    activeFrames: 3,
    recoveryFrames: 12,
    hitstunFrames: 24,
    damage: 5,
    startupSprite: PLAYER_J_5A_STARTUP,
    activeSprite: PLAYER_J_5A_ACTIVE,
    recoverySprite: PLAYER_J_5A_RECOVERY,
    moveFunction: nullptr,
    knockback: &knockback_J5A,
    hitboxData: ConstHitbox {
        xOffset: 8,
        yOffset: 0,
        width: 14,
        height: 20
    }
};

const Move MOVE_J_5B = {
    startupFrames: 10,
    activeFrames: 6,
    recoveryFrames: 16,
    hitstunFrames: 28,
    damage: 10,
    startupSprite: PLAYER_J_5B_STARTUP,
    activeSprite: PLAYER_J_5B_ACTIVE,
    recoverySprite: PLAYER_J_5B_RECOVERY,
    moveFunction: nullptr,
    knockback: &knockback_J5A,
    hitboxData: ConstHitbox {
        xOffset: 8,
        yOffset: 10,
        width: 14,
        height: 20
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
    moveFunction: nullptr,
    knockback: nullptr,
    hitboxData: ConstHitbox {
        xOffset: ,
        yOffset: ,
        width: ,
        height: 
    }
};

*/