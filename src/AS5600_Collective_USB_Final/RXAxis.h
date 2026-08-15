#ifndef RXAXIS_H
#define RXAXIS_H

#include <Arduino.h>

void RXAxis_Init();

int8_t updateRXAxis();

void RXAxis_SetCalibration(
    uint16_t min,
    uint16_t max
);

#endif