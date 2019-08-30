#ifndef PROJECTILE_CPP
#define PROJECTILE_CPP

#include <avr/pgmspace.h>

#include "hitbox.h"
#include "projectile.h"
#include "spriteData.h"

Projectile fireball = {
    x: 200,
    y: 200,
    damage: 0,
    direction: true,
    sprite: PLAYER_2B_ACTIVE,
    hitbox: Hitbox {
        x: 0,
        y: 0,
        width: 16,
        height: 16
    }
};

Projectile *fireballPtr = &fireball;

void updateFireball(Projectile *fireball) {
    // Check if the fireball is onscreen
    if (fireball->x < 128 || fireball->x > 255 - fireball->hitbox.width) {
        if (fireball->direction)
            ++fireball->x;
        else
            --fireball->x;
    }
}

#endif