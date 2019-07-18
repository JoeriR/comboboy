#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>
#include "hitbox.h"

bool collision(Hitbox *hitbox1, Hitbox *hitbox2);
bool isPointInBox(uint8_t x, uint8_t y, Hitbox *hitbox);

#endif