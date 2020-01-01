#ifndef HITBOX_CPP
#define HITBOX_CPP

#include "hitbox.h"

// Doesn't detect collision between attacks and the dummy when the dummy is in the left corner
bool collisionUsingOverlap(Hitbox *hitbox1, Hitbox *hitbox2) {

    bool doesWidthOverlap = (hitbox1->x <= (hitbox2->x + hitbox2->width)) && ((hitbox1->x + hitbox1->width) >= hitbox2->x);
    bool doesHeightOverlap = (hitbox1->y <= (hitbox2->y + hitbox2->height)) && ((hitbox1->y + hitbox1->height) >= hitbox2->y);

    return doesWidthOverlap && doesHeightOverlap;
}

// Doesn't detect collision when the dummy is in the middle huge hitbox that is bigger than the dummy itself
bool collisionWithCornersOnly(Hitbox *hitbox1, Hitbox *hitbox2) {
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

// Both collision fuctions have quirks, so call them both to get working collisions in any situation
bool collision(Hitbox *hitbox1, Hitbox *hitbox2) {
    return collisionWithCornersOnly(hitbox1, hitbox2) || collisionUsingOverlap(hitbox1, hitbox2);
}

#endif