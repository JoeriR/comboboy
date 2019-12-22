#ifndef KNOCKBACK_H
#define KNOCKBACK_H

#include <Arduino.h>

// Define Knockback Properties
#define CB_KB_PROP_NONE             0b00000000
#define CB_KB_PROP_LAUNCH           0b00000001  // Allow this knockback to push the dummy off the ground and into the air
#define CB_KB_PROP_WALLBOUNCE       0b00000010
#define CB_KB_PROP_GROUNDBOUNCE     0b00000100

typedef struct Knockback {
    int8_t horizontalDistance;
    int8_t verticalDistance;
    uint8_t ticksPerFrame;
    uint8_t tickLimit;
    uint8_t properties;
    void(*knockbackFunction)();
} Knockback;

void setKnockback(Knockback *knockback);

#endif