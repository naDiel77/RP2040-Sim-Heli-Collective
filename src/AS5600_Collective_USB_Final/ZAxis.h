#ifndef ZAXIS_H
#define ZAXIS_H

#include <Arduino.h>

void ZAxis_Init();

int8_t updateZAxis(uint16_t raw);

void ZAxis_SetCalibration(
    uint16_t min,
    uint16_t max
);

#endif