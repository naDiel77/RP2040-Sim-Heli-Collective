#include "StatusLED.h"
#include <NeoPixelConnect.h>
#include "Config.h"

NeoPixelConnect rgb(
    RGB_PIN,
    RGB_COUNT,
    pio0,
    0
);

void StatusLED_Init()
{
    rgb.neoPixelFill(
        0,
        0,
        0,
        true
    );

}

void setStatus(
    SystemStatus status
)
{

    switch(status)
    {
        case STATUS_ERROR:

            // GRB Reihenfolge beachten
            rgb.neoPixelFill(
                0,
                255,
                0,
                true
            );

            break;

        case STATUS_OK:

            // GRB = Grün
            rgb.neoPixelFill(
                255,
                0,
                0,
                true
            );

            break;

        case STATUS_CALIBRATION:

            // GRB = Blau
            rgb.neoPixelFill(
                0,
                0,
                255,
                true
            );

            break;
    }

}