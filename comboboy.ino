#ifndef COMBOBOY_INO
#define COMBOBOY_INO

#include <Arduboy2.h>
#include <Arduino.h>

#include "src/buffer.h"
#include "src/dummy.h"
#include "src/engine.h"
#include "src/input.h"
#include "src/player.h"
#include "src/spriteData.h"

Arduboy2 arduboy;

// make an ArdBitmap instance that will use the given the screen buffer and dimensions
#define ARDBITMAP_SBUF arduboy.getBuffer()
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;


// Constants
const uint8_t FRAME_RATE = 60;

// Global variables
uint8_t globalColor = 0;
uint8_t input = 0x00;

bool doDisplayTitlescreen = true;

void handleTitlescreen() {
    if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON)) {
        doDisplayTitlescreen = false;
    }
    else {
        arduboy.clear();

        // Draw Titlescreen text
        arduboy.setCursor(2, 2);
        arduboy.print(F("Combo Boy"));

        arduboy.setCursor(2, 12);
        arduboy.print(F("Made by Joeri"));

        arduboy.setCursor(2, 22);
        arduboy.print(F("V 0.4 (DEVELOP)"));

        arduboy.setCursor(10, 42);
        arduboy.print(F("Press A/B to play"));

        arduboy.display();
    }
}

// Reads the held buttons and sets the corresponding bits in the input byte
void updateInput() {
    input = 0x00;

    if (arduboy.pressed(RIGHT_BUTTON))
        input += CB_RIGHT_BUTTON;
    if (arduboy.pressed(LEFT_BUTTON))
        input += CB_LEFT_BUTTON;
    if (arduboy.pressed(UP_BUTTON))
        input += CB_UP_BUTTON;
    if (arduboy.pressed(DOWN_BUTTON))
        input += CB_DOWN_BUTTON;
    if (arduboy.justPressed(A_BUTTON)) // TEMP: Change it back to pressed() when the input-buffer has been implemented
        input += CB_A_BUTTON;
    if (arduboy.justPressed(B_BUTTON)) // TEMP: See comment above
        input += CB_B_BUTTON;
}

inline uint8_t handleMirroring(bool direction) {
    if (direction)
        return MIRROR_NONE;
    else
        return MIRROR_HORIZONTAL;
}

void setup() {
    arduboy.boot();
    arduboy.setFrameRate(FRAME_RATE);

    initBuffer();

    Serial.begin(9600);     // Enable Serial
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

    arduboy.pollButtons();

    updateInput();

    updateGame(input);

    // DEBUG print, can be removed later
    if (detectQuarterCircleForward()) {
        arduboy.setCursor(100, 18);
        arduboy.print(F("QCF"));
    }

    // Draw comboTimerDisplay and draw damage
    if (comboDisplayTimer < comboDisplayTimerLimit) {
        arduboy.setCursor(2, 10);
        arduboy.print(comboCounterDisplay);
        arduboy.print(F(" Hits"));

        arduboy.setCursor(2, 18);
        arduboy.print(comboDamageDisplay);
        arduboy.print(F(" Dmg"));

        arduboy.setCursor(2, 26);
        arduboy.print(currentHitDamage);
        arduboy.print(F(" Dmg hit"));
    }

    // Draw screen boundaries
    arduboy.drawRect(0, 0, 128, 64);

    // Write Work In Progress message
    arduboy.setCursor(2, 2);
    arduboy.print(F("Comboboy WIP - Joeri"));

    // Draw player and dummy
    ardbitmap.drawBitmap(player.x + player.xOffset, player.y + player.yOffset, player.sprite, 16, 24, WHITE, ALIGN_NONE, handleMirroring(player.direction));
    ardbitmap.drawBitmap(dummy.x, dummy.y, dummy.sprite, 16, 16, WHITE, ALIGN_NONE, handleMirroring(!player.direction));

    // Draw fireball
    ardbitmap.drawBitmap(fireballPtr->x, fireballPtr->y, fireballPtr->sprite, 16, 24, WHITE, ALIGN_NONE, handleMirroring(fireballPtr->direction));

    // Draw hitbox of active move
    if (player.state == PlayerState::ExecutingMove && getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active) {

        uint8_t xPositionHitbox;
            if (player.direction)
                xPositionHitbox = player.x + player.currentMove->hitboxData.xOffset;
            else
                xPositionHitbox = player.x + 16 - player.currentMove->hitboxData.xOffset - player.currentMove->hitboxData.width;
            
        Hitbox tempHitbox = {
            x : xPositionHitbox,
            y : player.y + player.currentMove->hitboxData.yOffset,
            width : player.currentMove->hitboxData.width,
            height : player.currentMove->hitboxData.height
        }; 

        //arduboy.drawRect(tempHitbox.x, tempHitbox.y, tempHitbox.width, tempHitbox.height);
    }

    arduboy.display();
}

#endif