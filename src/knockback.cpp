#ifndef KNOCKBACK_CPP
#define KNOCKBACK_CPP

#include "knockback.h"
#include "engine.h"

void setKnockback(Knockback *knockback) {
    int8_t horizontalDistanceVar = player.direction ? knockback->horizontalDistance : knockback->horizontalDistance * -1;

    dummy.knockback = Knockback {
        horizontalDistance: horizontalDistanceVar,   // Adjusts knockback for side switching
        verticalDistance: knockback->verticalDistance,
        ticksPerFrame: knockback->ticksPerFrame,
        tickLimit: knockback->tickLimit,
        knockbackFunction: knockback->knockbackFunction
    };
}

#endif