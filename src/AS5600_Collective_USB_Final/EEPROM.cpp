#include "EEPROM.h"
#include <EEPROM.h>
#include "Config.h"

void EEPROM_Init()
{
    EEPROM.begin(EEPROM_SIZE);
}

bool loadCalibration(CalibrationData &data)
{
    EEPROM.get(
        0,
        data
    );
    if(data.magic != EEPROM_MAGIC)
        return false;
    return true;
}

void saveCalibration(CalibrationData &data)
{
    data.magic =
        EEPROM_MAGIC;
    EEPROM.put(
        0,
        data
    );
    EEPROM.commit();
}