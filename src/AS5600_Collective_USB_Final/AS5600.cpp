#include "AS5600.h"
#include <Wire.h>
#include "Config.h"

// =====================================
// AS5600 Init
// =====================================

bool AS5600_Init()
{
    Wire1.setSDA(SDA_PIN);
    Wire1.setSCL(SCL_PIN);
    Wire1.begin();
    Wire1.setClock(400000);
    delay(10);
    uint16_t raw;

    if(readAS5600(raw))
    {
        return true;
    }

    return false;
}

// =====================================
// RAW Angle lesen
// =====================================

bool readAS5600(uint16_t &raw)
{
    Wire1.beginTransmission(AS5600_ADDR);
    Wire1.write(RAW_ANGLE_H);
    if(Wire1.endTransmission()!= 0)
    {
        return false;
    }
    Wire1.requestFrom(
        AS5600_ADDR,
        (uint8_t)2
    );
    if(Wire1.available()!=2)
    {
        return false;
    }
    uint8_t high = Wire1.read();
    uint8_t low = Wire1.read();
    raw =
        ((high << 8) | low)
        &
        0x0FFF;
    return true;
}

// =====================================
// Status Register
// =====================================

uint8_t readAS5600Status()
{
    Wire1.beginTransmission(AS5600_ADDR);
    Wire1.write(STATUS_REG);
    if(
        Wire1.endTransmission()
        !=0
    )
    {
        return 0;
    }
    Wire1.requestFrom(
        AS5600_ADDR,
        (uint8_t)1
    );
    if(Wire1.available()
    )
    {
        return Wire1.read();
    }
    return 0;
}