#ifndef HITBOX_H
#define HITBOX_H

#include <Arduino.h>


// This struct stores const data for hitboxes
// It's position is relative to the players x- and y-coordinates
typedef struct ConstHitbox {
    const uint8_t xOffset;
    const uint8_t yOffset;
    const uint8_t width;
    const uint8_t height;
} ConstHitbox;

typedef struct Hitbox {
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
} Hitbox;

bool collision(Hitbox *hitbox1, Hitbox *hitbox2);
bool isPointInBox(uint8_t x, uint8_t y, Hitbox *hitbox);

#endif