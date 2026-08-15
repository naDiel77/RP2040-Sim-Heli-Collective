#ifndef EEPROM_MODULE_H
#define EEPROM_MODULE_H

#include "Types.h"

void EEPROM_Init();

bool loadCalibration(CalibrationData &data);

void saveCalibration(CalibrationData &data);

#endif