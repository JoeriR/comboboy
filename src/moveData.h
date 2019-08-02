#ifndef MOVEDATA_H
#define MOVEDATA_H

#include <avr/pgmspace.h>

#include "move.h"
#include "spriteData.h"

const Move MOVE_5A = {
    startupFrames: 6,
    activeFrames: 3,
    recoveryFrames: 12,
    hitstunFrames: 24,
    damage: 50,
    startupSprite: PLAYER_5A_STARTUP,
    activeSprite: PLAYER_5A_ACTIVE,
    recoverySprite: PLAYER_5A_RECOVERY,
    hitboxData: ConstHitbox {
        xOffset: 8,
        yOffset: 0,
        width: 8,
        height: 16
    }
};

#endif