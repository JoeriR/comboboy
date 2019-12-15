#ifndef KNOCKBACKDATA_H
#define KNOCKBACKDATA_H

#include "knockback.h"

Knockback knockback_default = {
    horizontalDistance: 0,
    verticalDistance: 0,
    ticksPerFrame: 0,
    tickLimit: 0,
    knockbackFunction: nullptr
};

Knockback knockback_5B = {
    horizontalDistance: 2,
    verticalDistance: 0,
    ticksPerFrame: 1,
    tickLimit: 10,
    knockbackFunction: nullptr
};

#endif