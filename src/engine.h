#ifndef ENGINE_H
#define ENGINE_H

#include <Arduino.h>

#include "player.h"
#include "dummy.h"
#include "move.h"

// Functions
void initGame();
void updateGame(uint8_t input);

// Variables
extern short comboCounter;
extern short comboCounterDisplay;
extern uint8_t comboDisplayTimerLimit;
extern uint8_t comboDisplayTimer;

extern uint8_t hitStunDecay;

extern Player player;

extern Move fiveA; 

extern Dummy dummy;

#endif