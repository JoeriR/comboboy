#ifndef KNOCKBACKDATA_H
#define KNOCKBACKDATA_H

#include "knockback.h"
#include "engine.h"

void knockbackFunctionJ214A() {
    if (player.direction)
        dummy.x += 2;
    else 
        dummy.x -= 2;

    ++dummy.y;

    if (dummy.y == 64 - 16) {

        uint8_t horizontalKnockback = 1;

        if (!player.direction)
            horizontalKnockback = -1;

        dummy.knockback = Knockback {
            horizontalDistance: horizontalKnockback,
            verticalDistance: 1,
            ticksPerFrame: 1,
            tickLimit: 5,
            properties: 0,
            knockbackFunction: nullptr
        };
    }
}

// Positive verticalDistance means the dummy moves upwards
// Negative verticalDistance means the dummy moves downwards
Knockback knockback_default = {
    horizontalDistance: 0,
    verticalDistance: 0,
    ticksPerFrame: 0,
    tickLimit: 0,
    properties: 0,
    knockbackFunction: nullptr
};

Knockback knockback_weak = {
    horizontalDistance: 1,
    verticalDistance: 1,
    ticksPerFrame: 1,
    tickLimit: 5,
    properties: 0,
    knockbackFunction: nullptr
};

Knockback knockback_J5A = {
    horizontalDistance: 1,
    verticalDistance: 1,
    ticksPerFrame: 1,
    tickLimit: 4,
    properties: 0,
    knockbackFunction: nullptr
};

Knockback knockback_2B = {
    horizontalDistance: 1,
    verticalDistance: 1,
    ticksPerFrame: 1,
    tickLimit: 3,
    properties: CB_KB_PROP_LAUNCH,
    knockbackFunction: nullptr
};

Knockback knockback_5B = {
    horizontalDistance: 1,
    verticalDistance: 1,
    ticksPerFrame: 1,
    tickLimit: 5,
    properties: 0,
    knockbackFunction: nullptr
};

Knockback knockback_236A_fireball = {
    horizontalDistance: 1,
    verticalDistance: 1,
    ticksPerFrame: 1,
    tickLimit: 3,
    properties: 0,
    knockbackFunction: nullptr
};

Knockback knockback_J_214A = {
    horizontalDistance: 1,
    verticalDistance: -1,
    ticksPerFrame: 1,
    tickLimit: 1,
    properties: 0,
    knockbackFunction: knockbackFunctionJ214A
};

#endif

/*
// Copy and paste base for convenience:

Knockback knockback_ = {
    horizontalDistance: 0,
    verticalDistance: 0,
    ticksPerFrame: 0,
    tickLimit: 0,
    properties: 0,
    knockbackFunction: nullptr
};

*/