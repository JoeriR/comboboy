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
    despawnAfterHitstop: false,
    sprite: PLAYER_2B_ACTIVE,
    hitbox: Hitbox {
        x: 200,
        y: 200,
        width: 16,
        height: 16
    }
};

Projectile *fireballPtr = &fireball;

void despawnProjectile(Projectile *projectile) {
    projectile->x = 200;
    projectile->y = 200;

    projectile->hitbox.x = 200;
    projectile->hitbox.y = 200;
}

void updateFireball(Projectile *fireball) {
    // Check if the fireball is onscreen
    if (isProjectileOnScreen(fireball)) {
        if (fireball->direction)
            ++fireball->x;
        else
            --fireball->x;

        fireball->hitbox.x = fireball->x;
        fireball->hitbox.y = fireball->y;
    }
}

bool isProjectileOnScreen(Projectile *projectile) {
    if (projectile->x < 128 || projectile->x > 255 - projectile->hitbox.width) 
        if (projectile->y < 64)
            return true;
    
    return false;
}

#endif