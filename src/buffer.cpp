#ifndef BUFFER_CPP
#define BUFFER_CPP

#define BUFFER_SIZE 20

#include "buffer.h"
#include "input.h"

uint8_t buffer[BUFFER_SIZE] = {};

uint8_t *startAddress = nullptr;
uint8_t *endAddress = nullptr;
uint8_t *bufferStart = nullptr;
uint8_t *bufferEnd = nullptr;

void initBuffer() {
    startAddress = buffer;
    endAddress = buffer + BUFFER_SIZE - 1;

    bufferStart = startAddress;
    bufferEnd = startAddress;
}

// Increments a pointer, however we set it back to the start of the memory area
//		when it reaches the end of the memory area where the buffer is stored
inline void incrementBufferPointer(uint8_t **pointer) {
	if (*pointer < endAddress)
		++(*pointer);
	else
		*pointer = startAddress;
}

void pushIntoBuffer(uint8_t input) {
	incrementBufferPointer(&bufferEnd);
    
    // Shift startpointer one address ahead if we have run out of space and have wrapped around
    if (bufferStart == bufferEnd) 
		incrementBufferPointer(&bufferStart);
    
    *bufferEnd = input;
}

bool detectQuarterCircleForward() {
    uint8_t *pointer = bufferStart;

    uint8_t counter = 0;

    bool downFound = false;
    bool downForwardFound = false;
    bool forwardFound = false;

    // If a quartercircle forward was detected in x amount of previous frames, then return true
    static uint8_t quarterCircleForwardDetectedFrames = 0;

    if (quarterCircleForwardDetectedFrames > 0) {
        --quarterCircleForwardDetectedFrames;
        return true;
    }

	// Go one spot further than bufferEnd?
    while (pointer != bufferEnd) {
		if (*pointer == CB_DOWN_BUTTON) {
			downFound = true;
			counter = 1;
		}
        else if (downFound && *pointer == CB_DOWN_BUTTON + CB_RIGHT_BUTTON)
            downForwardFound = true;
        else if (downForwardFound && *pointer == CB_RIGHT_BUTTON)
            forwardFound = true;

		incrementBufferPointer(&pointer);

		if (counter > 0)
			++counter;

        if (counter > 15)
            downFound = false;
    }

    if (downFound && downForwardFound && forwardFound) {
        quarterCircleForwardDetectedFrames = 20;
        return true;
    }
    else
        return false;
}

void printBufferToSerial() {
    uint8_t *pointer = bufferStart;

    while (pointer != bufferEnd) {
        Serial.print(*pointer, BIN);
        Serial.print("\n");
        incrementBufferPointer(&pointer);
    }
}

#endif