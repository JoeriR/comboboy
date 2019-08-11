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
extern short comboCounter;
extern short comboCounterDisplay;
extern uint8_t comboDisplayTimerLimit;
extern uint8_t comboDisplayTimer;

extern uint8_t hitStunDecay;

extern bool didPlayerHitMoveThisFrame;

extern Player player;

extern Dummy dummy;

#endif