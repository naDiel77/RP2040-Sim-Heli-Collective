#include "ZAxis.h"

#include "Config.h"

// =====================================
// Kalibrierwerte (später EEPROM)
// =====================================

static uint16_t zMin = 4095;
static uint16_t zMax = 0;
//Test
//static uint16_t zMin = 2087;
//static uint16_t zMax = 2515;

// =====================================
// Filter Variablen
// =====================================

static float filteredValue = 0;
static float velocity = 0;

// =====================================
// Init
// =====================================

void ZAxis_Init()
{
    filteredValue = 0;
    velocity = 0;
}

void ZAxis_SetCalibration(
    uint16_t min,
    uint16_t max
)
{

    if(min < max)
    {
        zMin = min;
        zMax = max;
    }
}

// =====================================
// Alpha-Beta Filter
// =====================================

static float filterZ(
    float measurement
)
{
    float prediction =
        filteredValue + velocity;
    float error =
        measurement - prediction;
    filteredValue =
        prediction +
        FILTER_ALPHA * error;
    velocity =
        velocity +
        FILTER_BETA * error;
    return filteredValue;
}

// =====================================
// Skalierung
// =====================================

static int8_t scaleZ(
    uint16_t raw
)
{
    if(raw < zMin)
        raw = zMin;
    if(raw > zMax)
        raw = zMax;
    int value =
        map(
            raw,
            zMin,
            zMax,
            -127,
            127
        );
    value =
        constrain(
            value,
            -127,
            127
        );
#ifdef INVERT_Z
    if(INVERT_Z)
        value = -value;
#endif
    return (int8_t)value;
}

// =====================================
// Update
// =====================================

int8_t updateZAxis(uint16_t raw)
{
    float filtered = filterZ(raw);
    return scaleZ((uint16_t)filtered);
}