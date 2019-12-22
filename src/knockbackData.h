#ifndef KNOCKBACKDATA_H
#define KNOCKBACKDATA_H

#include "knockback.h"

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
    horizontalDistance: 2,
    verticalDistance: 1,
    ticksPerFrame: 1,
    tickLimit: 10,
    properties: 0,
    knockbackFunction: nullptr
};

Knockback knockback_J5A = {
    horizontalDistance: 2,
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
    horizontalDistance: 2,
    verticalDistance: 2,
    ticksPerFrame: 1,
    tickLimit: 10,
    properties: 0,
    knockbackFunction: nullptr
};

Knockback knockback_236A_fireball = {
    horizontalDistance: 3,
    verticalDistance: 1,
    ticksPerFrame: 5,
    tickLimit: 11,
    properties: 0,
    knockbackFunction: nullptr
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