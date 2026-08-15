#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <Arduino.h>
#include "Types.h"

extern CalibrationData cal;

void Calibration_Init();

void Calibration_Start();

void Calibration_Update();

#endif