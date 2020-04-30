#ifndef KNOCKBACKDATA_H
#define KNOCKBACKDATA_H

#include "knockback.h"
#include "engine.h"

// Move the Dummy down with the Player untill the Dummy hits the ground
// Then change the knockback to a slow slide along the ground
void knockbackFunctionJ214ACharged() {
    if (player.direction) {
        dummy.x = player.x + 16;
        dummy.y = player.y + 24;
    }
    else {
        dummy.x = player.x -16;
        dummy.y = player.y + 24;
    }

    if (dummy.y >= 64 - 16) {

        uint8_t horizontalKnockback = 1;

        if (!player.direction)
            horizontalKnockback = -1;

        dummy.knockback = Knockback {
            horizontalDistance: horizontalKnockback,
            verticalDistance: 0,
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

// TODO: Tweak these numbers
Knockback knockback_J_214A = {
    horizontalDistance: 2,
    verticalDistance: -1,
    ticksPerFrame: 1,
    tickLimit: 3,
    properties: 0,
    knockbackFunction: nullptr
};

Knockback knockback_J_214A_charged = {
    horizontalDistance: 1,
    verticalDistance: -1,
    ticksPerFrame: 1,
    tickLimit: 1,
    properties: 0,
    knockbackFunction: knockbackFunctionJ214ACharged
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