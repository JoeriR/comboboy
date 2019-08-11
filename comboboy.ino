#ifndef COMBOBOY_INO
#define COMBOBOY_INO

#include <Arduboy2.h>
#include <Arduino.h>

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

void setup() {
    arduboy.boot();
    arduboy.setFrameRate(FRAME_RATE);

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

    // Draw comboTimerDisplay
    if (comboDisplayTimer < comboDisplayTimerLimit) {
        arduboy.setCursor(2, 10);
        arduboy.print(comboCounterDisplay);
        arduboy.write(" Hits");
    }

    // Draw screen boundaries
    arduboy.drawRect(0, 0, 128, 64);

    // Write Work In Progress message
    arduboy.setCursor(2, 2);
    arduboy.write("Comboboy WIP - Joeri");

    ardbitmap.drawBitmap(player.x, player.y, player.sprite, 16, 24, WHITE, ALIGN_NONE, MIRROR_NONE);
    ardbitmap.drawBitmap(dummy.x, dummy.y, dummy.sprite, 16, 16, WHITE, ALIGN_NONE, MIRROR_NONE);

    // Draw hitbox of active move
    if (player.state == PlayerState::ExecutingMove && getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active) {

        Hitbox tempHitbox = {
            x: player.x + player.currentMove->hitboxData.xOffset,
            y: player.y + player.currentMove->hitboxData.yOffset,
            width: player.currentMove->hitboxData.width,
            height: player.currentMove->hitboxData.height
        };

        arduboy.drawRect(tempHitbox.x, tempHitbox.y, tempHitbox.width, tempHitbox.height);
    }

    arduboy.display();
}

#endif