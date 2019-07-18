#ifndef COMBOBOY_INO
#define COMBOBOY_INO

#include <Arduino.h>
#include <Arduboy2.h>

#include "src/spriteData.h"
#include "src/player.h"
#include "src/dummy.h"
#include "src/util.h"

Arduboy2 arduboy;


// make an ArdBitmap instance that will use the given the screen buffer and dimensions
#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;

// Constants
const uint8_t FRAME_RATE = 60;

// Global variables
uint8_t globalColor = 0;
bool doDisplayTitlescreen = true;

short comboCounter = 0;
short comboCounterDisplay = 0;
uint8_t comboDisplayTimerLimit = 120;
uint8_t comboDisplayTimer = comboDisplayTimerLimit; // Start at the limit, so the comboDisplay doesn't get drawn at launch

uint8_t hitStunDecay = 0;

Player player = {
  x: 32,
  y: 64 - 13,
  currentMove: nullptr,
  currentMoveFrameCounter: 0,
  state: PlayerState::Idle,
  sprite: PLAYER_IDLE,
  hitbox: Hitbox {
    x: 0,
    y: 0,
    width: 16,
    height: 16
  }
};

Move fiveA = {
  startupFrames: 6,
  activeFrames: 3,
  recoveryFrames: 12,
  hitstunFrames: 24,
  damage: 50,
  startupSprite: PLAYER_5A_STARTUP,
  activeSprite: PLAYER_5A_ACTIVE,
  recoverySprite: PLAYER_5A_RECOVERY,
  hitboxData: ConstHitbox {
    xOffset: 8,
    yOffset: 0,
    width: 8,
    height: 16
  }
};

Dummy dummy = {
  x: 96,
  y: 64 - 9,
  stunnedFrames: 0,
  recoveryFrames: 0,
  state: DummyState::Idle,
  sprite: DUMMY_IDLE,
  hitbox: Hitbox {
    x: 0,
    y: 0,
    width: 16,
    height: 16
  }
};






void testGameCode() {

  if (player.state == PlayerState::Idle) {
    player.sprite = PLAYER_IDLE;
  }

  // TODO: Use the Player's Hitbox for collision detection against the walls and the dummy
  if (arduboy.pressed(RIGHT_BUTTON) && player.x < 128 - 6 && player.state != PlayerState::ExecutingMove) {
    ++player.x;
  }

  if (arduboy.pressed(LEFT_BUTTON) && player.x > 0 + 5 && player.state != PlayerState::ExecutingMove) {
    --player.x;
  }

  

  // TODO: make the player execute the 5a move
  if (arduboy.pressed(A_BUTTON) && player.state != PlayerState::ExecutingMove) {
    player.currentMove = &fiveA;
    player.currentMoveFrameCounter = 0;
    player.currentMoveHit = false;    // CARE:
    player.state = PlayerState::ExecutingMove;
  }

  if (player.state == PlayerState::ExecutingMove) {

    // If the move has ended, return the player to idle state
    // Else, continue executing the move
    if (player.currentMoveFrameCounter >= player.currentMove->startupFrames + player.currentMove->activeFrames + player.currentMove->recoveryFrames) {
      playerSetIdle(&player);
    }
    else {
      MoveState moveState = getMoveState(player.currentMove, player.currentMoveFrameCounter);

      if (moveState == MoveState::Startup)
        player.sprite = player.currentMove->startupSprite;
      else if (moveState == MoveState::Active)
        player.sprite = player.currentMove->activeSprite;
      else if (moveState == MoveState::Recovery)
        player.sprite = player.currentMove->recoverySprite;
      else if (moveState == MoveState::Finished) 
        player.sprite = PLAYER_IDLE;
      else 
        player.sprite = PLAYER_IDLE;
    }
    
    ++player.currentMoveFrameCounter;
  }

  // Check if player is executing a move and if that move colides with the dummy
  if (player.state == PlayerState::ExecutingMove && getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active && !player.currentMoveHit) {

    Hitbox playerMoveHitbox = {
      x: player.x + player.currentMove->hitboxData.xOffset,
      y: player.y + player.currentMove->hitboxData.yOffset,
      width: player.currentMove->hitboxData.width,
      height: player.currentMove->hitboxData.height
    };

    dummy.hitbox.x = dummy.x;
    dummy.hitbox.y = dummy.y;

    if (collision(&playerMoveHitbox, &dummy.hitbox)) {
      player.currentMoveHit = true;

      // Put the dummy in hitstun
      dummy.stunnedFrames = player.currentMove->hitstunFrames - hitStunDecay;

      // Increase comboCounter
      ++comboCounter;
      comboCounterDisplay = comboCounter;

      comboDisplayTimer = 0;

      // Update hitStunDecay
      ++hitStunDecay;
    }
  }

  // Update Dummy
  if (dummy.stunnedFrames > 0) {
    dummy.state = DummyState::Hit;

    --dummy.stunnedFrames;

    if (dummy.stunnedFrames == 0) {
      dummy.state = DummyState::Recovery;   // TODO: implement dummy recovery animation and logic
      dummy.recoveryFrames = 20;
    }

  }
  else {
    dummy.state = DummyState::Idle;
  }

  switch (dummy.state) {
    case DummyState::Idle : dummy.sprite = DUMMY_IDLE; break;
    case DummyState::Hit : dummy.sprite = DUMMY_HIT; break;
    case DummyState::Recovery : dummy.sprite = DUMMY_IDLE; break;
    default: dummy.sprite = DUMMY_IDLE;
  }


  // Update and draw the comboDisplayTimer
  if (comboDisplayTimer < comboDisplayTimerLimit) {
    ++comboDisplayTimer;

    arduboy.setCursor(2, 10);
    arduboy.print(comboCounterDisplay);
    arduboy.write(" Hits");
  }

  if (dummy.state == DummyState::Idle) {
    comboCounter = 0;

    hitStunDecay = 0;
  }

}



void handleTitlescreen() {
  if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
    doDisplayTitlescreen = false;
  }
  else {
    arduboy.clear();

    // Draw Titlescreen text
    arduboy.setCursor(2, 2);
    arduboy.write("Combo Boy");

    arduboy.setCursor(2, 12);
    arduboy.write("Made by Joeri");

    arduboy.setCursor(2, 22);
    arduboy.write("V 0.0.1");

    arduboy.setCursor(10, 42);
    arduboy.write("Press A/B to play");

    arduboy.display();
  }
}


void setup() {
  arduboy.begin();
  arduboy.setFrameRate(FRAME_RATE);
}

void loop() {
  if (!arduboy.nextFrame())
    return;

  if (doDisplayTitlescreen) {
    handleTitlescreen();
    return;
  }

  // Draw the screen
  arduboy.clear();

  testGameCode();

  // Draw screen boundaries
  arduboy.drawRect(0, 0, 128, 64);

  // Write Work In Progress message
  arduboy.setCursor(2, 2);
  arduboy.write("Comboboy WIP - Joeri");
  
  ardbitmap.drawBitmap(player.x, player.y, player.sprite, 16, 24, WHITE, ALIGN_CENTER, MIRROR_NONE);
  ardbitmap.drawBitmap(dummy.x, dummy.y, dummy.sprite, 16, 16, WHITE, ALIGN_CENTER, MIRROR_NONE);

  arduboy.display();
}

#endif