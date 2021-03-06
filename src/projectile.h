#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <avr/pgmspace.h>

#include "hitbox.h"

typedef struct Projectile {
    uint8_t x;
    uint8_t y;
    uint8_t damage;
    bool direction;
    bool despawnAfterHitstop;
    uint8_t const *sprite;
    Hitbox hitbox;
} Projectile;

extern Projectile *fireballPtr;

void despawnProjectile(Projectile *projectile);
bool isProjectileOnScreen(Projectile *projectile);
void updateFireball(Projectile *fireball);

#endif