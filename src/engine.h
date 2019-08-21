#ifndef ENGINE_H
#define ENGINE_H

#include <Arduino.h>

#include "dummy.h"
#include "move.h"
#include "player.h"


// Functions
void initGame();
void updateGame(uint8_t input);

// Variables
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