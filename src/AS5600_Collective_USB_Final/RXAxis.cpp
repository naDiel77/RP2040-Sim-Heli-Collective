#include "RXAxis.h"
#include "Config.h"

static int32_t rxFiltered = 0;
static float alpha = 0.15f;
static uint16_t rxMin = 49;
static uint16_t rxMax = 978;

// =====================================
// Initialisierung
// =====================================

void RXAxis_Init()
{
    pinMode(
        RX_PIN,
        INPUT
    );
    rxFiltered = analogRead(RX_PIN);
}

// =====================================
// Kalibrierung übernehmen
// =====================================

void RXAxis_SetCalibration(
    uint16_t min,
    uint16_t max
)
{
    if(min < max)
    {
        rxMin = min;
        rxMax = max;
    }
}

// =====================================
// RX lesen + filtern + skalieren
// =====================================

int8_t updateRXAxis()
{
    uint16_t raw;

    raw =
        analogRead(
            RX_PIN
        );

    // Alpha-Filter

    rxFiltered =
        rxFiltered +
        alpha *
        ((int32_t)raw - rxFiltered);

    // Skalieren

    int value =
        map(
            rxFiltered,
            rxMin,
            rxMax,
            -127,
            127
        );

    value =
        constrain(
            value,
            -127,
            127
        );


    return (int8_t)value;
}