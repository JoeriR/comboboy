#ifndef INPUT_H
#define INPUT_H

// This file contains the defines for how input is interpreted

/* 
    These defines make it easier to understand whats going on.
    To clarify, the input from the Arduboy is put in one byte.
    The engine will use the input given by the player to do things.
    The buffer will save inputs from previous frames in order to chain them together
        to execute special moves and super(s).
    
    Two bits are unused, they might get used later to store additional information
*/

#define CB_RIGHT_BUTTON 0b00000001
#define CB_LEFT_BUTTON  0b00000010
#define CB_UP_BUTTON    0b00000100
#define CB_DOWN_BUTTON  0b00001000
#define CB_A_BUTTON     0b00010000
#define CB_B_BUTTON     0b00100000

#endif