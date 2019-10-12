#ifndef ENGINE_CPP
#define ENGINE_CPP

#include "buffer.h"
#include "dummy.h"
#include "engine.h"
#include "hitbox.h"
#include "input.h"
#include "move.h"
#include "moveData.h"
#include "player.h"
#include "projectile.h"
#include "spriteData.h"


// Vars
uint16_t comboCounter = 0;
uint16_t comboCounterDisplay = 0;
uint8_t comboDisplayTimerLimit = 120;
uint8_t comboDisplayTimer = comboDisplayTimerLimit;

uint16_t comboDamage = 0;
uint16_t comboDamageDisplay = 0;
uint8_t comboDamageScale = 100; // in percent

uint16_t currentHitDamage = 0;

uint8_t hitStunDecay = 0;

uint8_t hitStopFrames = 0;

bool didPlayerHitMoveThisFrame = false;

Player player = {
    x: 32,
    y: 64 - 25,
    xOffset: 0,
    yOffset: 0,
    currentMove: nullptr,
    currentMoveFrameCounter: 0,
    state: PlayerState::Idle,
    crouchFrame: 0,
    walkFrame: 0,
    crouchState: PlayerCrouchState::Standing,
    sprite: PLAYER_IDLE,
    hitbox: Hitbox {
        x: 0,
        y: 0,
        width: 16,
        height: 16
    }
};

Dummy dummy = {
    x: 96,
    y: 64 - 17,
    stunnedFrames: 0,
    recoveryFrames: 0,
    state: DummyState::Idle,
    sprite: DUMMY_IDLE,
    hitbox: Hitbox {
        x: 96,
        y: 64 - 17,
        width: 16,
        height: 16
    }
};



void handlePlayerPosition(uint8_t input) {
    PlayerWalkState playerWalkState = PlayerWalkState::Standing;

    // Only allow the player to move if they're not holding down (are crouching)
    if (!(input & CB_DOWN_BUTTON)) {
        if (input & CB_RIGHT_BUTTON && player.state != PlayerState::ExecutingMove && player.crouchState != PlayerCrouchState::Crouching) {
            ++player.x;
            playerWalkState = updatePlayerWalkFrame(&player);
        }

        if (input & CB_LEFT_BUTTON && player.state != PlayerState::ExecutingMove && player.crouchState != PlayerCrouchState::Crouching) {
            --player.x;
            playerWalkState = updatePlayerWalkFrame(&player);
        }

        if (playerWalkState == PlayerWalkState::Walk1)
            player.sprite = PLAYER_WALK_1;
        else if (playerWalkState == PlayerWalkState::Walk2)
            player.sprite = PLAYER_WALK_2;
    }
}

void handlePlayerCrouching(uint8_t input) {

    if (player.currentMove == &MOVE_2A)
        player.crouchFrame = CROUCH_FRAME_LIMIT;

    if (player.state != PlayerState::Idle) {
        if (player.currentMove != &MOVE_2A) {
            player.crouchFrame = 0;
        }
        return;
    }
    
    PlayerCrouchState crouchState = getPlayerCrouchState(&player, input);

    if (crouchState == PlayerCrouchState::InBetween) 
        player.sprite = PLAYER_CROUCH_INBETWEEN;
    if (crouchState == PlayerCrouchState::Crouching)
        player.sprite = PLAYER_CROUCH;
}

void handleInputBuffer(uint8_t input) {
    // Decide which move to execute depenging on the player's input and state
    // The Player can execute new moves if they're not currently performing a move.
    // However, they are allowed to execute a new move if their current move has hit the dummy!
    // (the Player can cancel moves on-hit)

    pushIntoBuffer(input);

    if (player.state != PlayerState::ExecutingMove || player.currentMoveHit) {
        
        if (detectQuarterCircleForward() && input & CB_A_BUTTON)
            playerExecuteMove(&player, &MOVE_236A);
        else if (input & CB_DOWN_BUTTON && input & CB_A_BUTTON)
            playerExecuteMove(&player, &MOVE_2A);
        else if (input & CB_A_BUTTON) 
            playerExecuteMove(&player, &MOVE_5A);
        else if (input & CB_DOWN_BUTTON && input & CB_B_BUTTON)
            playerExecuteMove(&player, &MOVE_2B);
        else if (input & CB_B_BUTTON)
            playerExecuteMove(&player, &MOVE_5B);
    }
}

void setPlayerSprite() {
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
}

void handleProjectiles(uint8_t input) {
    if (fireballPtr->despawnAfterHitstop)
        despawnProjectile(fireballPtr);

    updateFireball(fireballPtr);
}

// TODO: Currently only works properly when the player is facing right
bool handlePlayerDummyCollision(Player *player, Dummy *dummy) {
    bool didPlayerAndDummyCollide = isPointInBox(player->x + 16, player->y + 8, &dummy->hitbox) || isPointInBox(player->x + 16, player->y + 16, &dummy->hitbox) || isPointInBox(player->x + 16, player->y + 24, &dummy->hitbox);

    // Push the player left outside of the dummy if they collide
    if (didPlayerAndDummyCollide)
        player->x = dummy->x - 16;

    return didPlayerAndDummyCollide;
}

void handleCurrentMoveHit(Move const *movePtr = NULL) {

    if (movePtr == NULL)
        movePtr = player.currentMove;
        
    player.currentMoveHit = true;

    // Put the dummy in hitstun
    dummy.stunnedFrames = movePtr->hitstunFrames - hitStunDecay;

    // Set hitstop
    hitStopFrames = 15;

    // Increase comboCounter
    ++comboCounter;
    comboCounterDisplay = comboCounter;

    comboDisplayTimer = 0;

    // Calculate damage and add to comboDamage
    uint16_t scaledDamage = movePtr->damage * comboDamageScale;
    comboDamage += scaledDamage;
    comboDamageDisplay = comboDamage;

    currentHitDamage = scaledDamage;

    if (comboDamageScale > 10) {
        if (comboDamageScale > 50)
            comboDamageScale -= 10;
        else
            comboDamageScale -= 5;
    }

    // Update hitStunDecay
    ++hitStunDecay;
}

void handleCurrentMoveAndCollision() {
    // Check if player is executing a move and if that move colides with the dummy
    if (player.state == PlayerState::ExecutingMove) {
        
        // Execute a move's unique function if it has one
        if (player.currentMove->moveFunction != nullptr)
            player.currentMove->moveFunction();

        if (getMoveState(player.currentMove, player.currentMoveFrameCounter) == MoveState::Active && !player.currentMoveHit) {
            Hitbox playerMoveHitbox = {
                x : player.x + player.currentMove->hitboxData.xOffset,
                y : player.y + player.currentMove->hitboxData.yOffset,
                width : player.currentMove->hitboxData.width,
                height : player.currentMove->hitboxData.height
            };

            dummy.hitbox.x = dummy.x;
            dummy.hitbox.y = dummy.y;

            if (dummy.state != DummyState::Recovery && collision(&playerMoveHitbox, &dummy.hitbox)) {
                handleCurrentMoveHit();
                player.sprite = player.currentMove->activeSprite;
            }
        }
    }

    if (dummy.state != DummyState::Recovery && collision(&fireballPtr->hitbox, &dummy.hitbox)) {
        handleCurrentMoveHit(&MOVE_236A);
        fireballPtr->despawnAfterHitstop = true;
    }
    
}

void updateDummy() {
    // Update Dummy
    if (dummy.stunnedFrames > 0) {
        dummy.state = DummyState::Hit;

        --dummy.stunnedFrames;

        if (dummy.stunnedFrames == 0) {
            dummy.state = DummyState::Recovery;
            dummy.recoveryFrames = 60;
        }
    }
    else if (dummy.recoveryFrames > 0) {
        dummy.state = DummyState::Recovery;
        --dummy.recoveryFrames;
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
            dummy.sprite = DUMMY_RECOVERY;
            break;
        default:
            dummy.sprite = DUMMY_IDLE;
    }
}

void preventOutofBounds() {
    // Push player inwards towards the screen
    if (player.x > 128 + 64)
        player.x = 0;
    if (player.x > 128 - 16)
        player.x = 128 - 16;
    if (player.y > 64 + 64)
        player.y = 0;
    if (player.y > 64 - 25)
        player.y = 64 - 25;

    // Push dummy inwards towards the screen
    if (dummy.x > 128 + 64)
        dummy.x = 0;
    if (dummy.x > 128 - 16)
        dummy.x = 128 - 16;
    if (dummy.y > 64 + 64)
        dummy.y = 0;
    if (dummy.y > 64 - 17)
        dummy.y = 64 - 17;
}

void updateComboDisplayTimer() {
    // Update the comboDisplayTimer
    if (comboDisplayTimer < comboDisplayTimerLimit) {
        ++comboDisplayTimer;
    }

    if (dummy.state == DummyState::Idle) {
        comboCounter = 0;
        comboDamage = 0;
        comboDamageScale = 100;
        hitStunDecay = 0;
    }
}

void updateGame(uint8_t input) {

    // Force player sprite to be idle if state is idle, just in case
    if (player.state == PlayerState::Idle) {
        player.sprite = PLAYER_IDLE;
    }

    handleInputBuffer(input);

    if (hitStopFrames > 0) {
        --hitStopFrames;
    }
    else {
        player.xOffset = 0;
        player.yOffset = 0;
        handlePlayerPosition(input);

        setPlayerSprite();
        handlePlayerCrouching(input);

        handleProjectiles(input);

        handleCurrentMoveAndCollision();

        updateDummy();

        handlePlayerDummyCollision(&player, &dummy);

        preventOutofBounds();
        
        updateComboDisplayTimer();
    }
    
}

#endif