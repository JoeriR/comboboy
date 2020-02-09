#ifndef ENGINE_H
#define ENGINE_H

#include <Arduino.h>

#include "dummy.h"
#include "move.h"
#include "player.h"
#include "projectile.h"


// Functions
void updateGame(uint8_t input, uint8_t rawInputParam);
void resetGame();

// Variables
extern uint8_t playerInput;
extern uint8_t inputPrevFrame;
extern uint8_t rawInput;

extern uint16_t comboCounter;
extern uint16_t comboCounterDisplay;
extern uint8_t comboDisplayTimerLimit;
extern uint8_t comboDisplayTimer;

extern uint16_t comboDamage;
extern uint16_t comboDamageDisplay;
extern uint8_t comboDamageScale;

extern uint16_t currentHitDamage;

extern uint8_t hitStunDecay;

extern bool didPlayerHitMoveThisFrame;

extern Player player;

extern Dummy dummy;

#endif