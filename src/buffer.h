#ifndef BUFFER_H
#define BUFFER_H

#include <Arduino.h>


void pushIntoBuffer(uint8_t input);
bool detectQuarterCircleForward();
bool detectQuarterCircleBack();

void initBuffer();

void printBufferToSerial();

#endif