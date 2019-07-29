#ifndef DUMMY_H
#define DUMMY_H

#include <Arduino.h>

#include "hitbox.h"


enum class DummyState { Idle, Hit, Recovery };

typedef struct Dummy {
    uint8_t x;
    uint8_t y;
    uint8_t stunnedFrames;
    uint8_t recoveryFrames;
    DummyState state;
    uint8_t const *sprite;
    Hitbox hitbox;
} Dummy;

#endif