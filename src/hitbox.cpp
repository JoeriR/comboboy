#ifndef HITBOX_CPP
#define HITBOX_CPP

#include "hitbox.h"


bool collision(Hitbox *hitbox1, Hitbox *hitbox2) {
    bool result = isPointInBox(hitbox1->x, hitbox1->y, hitbox2) ||
                  isPointInBox(hitbox1->x + hitbox1->width, hitbox1->y, hitbox2) ||
                  isPointInBox(hitbox1->x, hitbox1->y + hitbox1->height, hitbox2) ||
                  isPointInBox(hitbox1->x + hitbox1->width, hitbox1->y + hitbox1->height, hitbox2);

    return result;
}

bool isPointInBox(uint8_t x, uint8_t y, Hitbox *hitbox) {
    if (x >= hitbox->x && x <= hitbox->x + hitbox->width)
        if (y >= hitbox->y && y <= hitbox->y + hitbox->height)
            return true;

    return false;
}

#endif