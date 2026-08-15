#include "Buttons.h"

// =====================================
// Button Pins
// =====================================

static const uint8_t buttonPins[BUTTON_COUNT] =
{
    27,     // Button 1 + Calibration
    0,      // Button 2
    1,      // Button 3
    2,      // Button 4
    3,      // Button 5
    4,      // Button 6
    5,      // Button 7
    6,      // Button 8
    7,      // Button 9
    8,      // Button 10
    9       // Button 11
};

// =====================================
// Entprellung
// =====================================

static bool buttonState[BUTTON_COUNT];
static bool lastReading[BUTTON_COUNT];
static uint32_t lastChangeTime[BUTTON_COUNT];
static const uint32_t debounceTime = 20;
//static uint32_t lastDebug = 0;

// =====================================
// Initialisierung
// =====================================

void Buttons_Init()
{
    for(uint8_t i = 0; i < BUTTON_COUNT; i++)
    {
        pinMode(buttonPins[i],INPUT_PULLUP);

        buttonState[i] = digitalRead(buttonPins[i]);

        lastReading[i] = buttonState[i];

        lastChangeTime[i] = millis();
    }
}


// =====================================
// Entprellung
// =====================================

void Buttons_Update()
{
    uint32_t now = millis();

    for(uint8_t i = 0; i < BUTTON_COUNT; i++)
    {
        bool reading = digitalRead(buttonPins[i]);

        if(reading != lastReading[i])
        {
            lastChangeTime[i] = now;
            lastReading[i] = reading;
        }
        if(
            (now - lastChangeTime[i]) >= debounceTime
        )
        {
            if(reading != buttonState[i])
            {
                buttonState[i] =reading;
            }
        }
    }
}

// =====================================
// Button Status
// =====================================

bool Button_Pressed(uint8_t index)
{
    if(index >= BUTTON_COUNT)
        return false;
    return (buttonState[index] == LOW);
}