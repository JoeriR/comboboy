#ifndef KNOCKBACK_H
#define KNOCKBACK_H

#include <Arduino.h>

typedef struct Knockback {
    int8_t horizontalDistance;
    int8_t verticalDistance;
    uint8_t ticksPerFrame;
    uint8_t tickLimit;
    void(*knockbackFunction)();
} Knockback;

void setKnockback(Knockback *knockback);

#endif