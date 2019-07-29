#ifndef ENGINE_CPP
#define ENGINE_CPP

#include "engine.h"
#include "hitbox.h"
#include "input.h"
#include "move.h"
#include "spriteData.h"


// Vars
short comboCounter = 0;
short comboCounterDisplay = 0;
uint8_t comboDisplayTimerLimit = 120;
uint8_t comboDisplayTimer = comboDisplayTimerLimit;

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

void updateGame(uint8_t input) {

    if (player.state == PlayerState::Idle) {
        player.sprite = PLAYER_IDLE;
    }

    // TODO: Use the Player's Hitbox for collision detection against the walls and the dummy
    if (input & CB_RIGHT_BUTTON && player.x < 128 - 6 && player.state != PlayerState::ExecutingMove) {
        ++player.x;
    }

    if (input & CB_LEFT_BUTTON && player.x > 0 + 5 && player.state != PlayerState::ExecutingMove) {
        --player.x;
    }

    // TODO: Make executing moves "generic" (let the buffer handle it, when it's done)
    if (input & CB_A_BUTTON && player.state != PlayerState::ExecutingMove) {
        player.currentMove = &fiveA;
        player.currentMoveFrameCounter = 0;
        player.currentMoveHit = false; // CARE:
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
    if (player.state == PlayerState::ExecutingMove &&
        getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active && !player.currentMoveHit) {

        Hitbox playerMoveHitbox = {
            x : player.x + player.currentMove->hitboxData.xOffset,
            y : player.y + player.currentMove->hitboxData.yOffset,
            width : player.currentMove->hitboxData.width,
            height : player.currentMove->hitboxData.height
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
            dummy.state = DummyState::Recovery; // TODO: implement dummy recovery animation and logic
            dummy.recoveryFrames = 20;
        }
    }
    else {
        dummy.state = DummyState::Idle;
    }

    switch (dummy.state) {
        case DummyState::Idle:
            dummy.sprite = DUMMY_IDLE;
            break;
        case DummyState::Hit:
            dummy.sprite = DUMMY_HIT;
            break;
        case DummyState::Recovery:
            dummy.sprite = DUMMY_IDLE;
            break;
        default:
            dummy.sprite = DUMMY_IDLE;
    }

    // Update the comboDisplayTimer
    if (comboDisplayTimer < comboDisplayTimerLimit) {
        ++comboDisplayTimer;
    }

    if (dummy.state == DummyState::Idle) {
        comboCounter = 0;
        hitStunDecay = 0;
    }
}

#endif