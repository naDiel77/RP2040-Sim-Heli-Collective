#ifndef AS5600_H
#define AS5600_H
#include <Arduino.h>

bool AS5600_Init();
bool readAS5600(uint16_t &raw);
uint8_t readAS5600Status();

#endif