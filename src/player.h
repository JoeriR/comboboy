#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "move.h"
#include "hitbox.h"

enum class  PlayerState {Idle, Walking, Dashing, ExecutingMove};

typedef struct Player
{
    uint8_t x;
    uint8_t y;
    Move *currentMove;
    uint8_t currentMoveFrameCounter;
    PlayerState state;
    uint8_t const *sprite;
    Hitbox hitbox;
    bool currentMoveHit;    // TODO: Replace this with a solution that supports with slow fireballs. Those will require their own bool or something else.
} Player;

void playerSetIdle(Player *player);

#endif