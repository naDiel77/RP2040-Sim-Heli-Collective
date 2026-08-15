#include "HatSwitch.h"
// =====================================
// HAT Pins
// =====================================

#define HAT_UP_PIN       10
#define HAT_RIGHT_PIN    11
#define HAT_DOWN_PIN     12
#define HAT_LEFT_PIN     13

// =====================================
// Entprellung
// =====================================

static bool hatState[4];
static bool lastReading[4];
static uint32_t lastChangeTime[4];
static const uint32_t debounceTime = 20;

// =====================================
// Initialisierung
// =====================================

void HatSwitch_Init()
{
    const uint8_t pins[4] =
    {
        HAT_UP_PIN,
        HAT_RIGHT_PIN,
        HAT_DOWN_PIN,
        HAT_LEFT_PIN
    };

    for(uint8_t i = 0; i < 4; i++)
    {
        pinMode(pins[i], INPUT_PULLUP);
        hatState[i] =
            digitalRead(
                pins[i]
            );
        lastReading[i] = hatState[i];
        lastChangeTime[i] = millis();
    }
}

// =====================================
// Entprellung
// =====================================

void HatSwitch_Update()
{
    const uint8_t pins[4] =
    {
        HAT_UP_PIN,
        HAT_RIGHT_PIN,
        HAT_DOWN_PIN,
        HAT_LEFT_PIN
    };

    uint32_t now = millis();

    for(uint8_t i = 0; i < 4; i++)
    {
        bool reading =
            digitalRead(
                pins[i]
            );

        if(reading != lastReading[i])
        {
            lastChangeTime[i] = now;
            lastReading[i] = reading;
        }

        if(
            (now - lastChangeTime[i])
            >= debounceTime
        )
        {
            if(reading != hatState[i])
            {
                hatState[i] = reading;
            }
        }
    }
}

// =====================================
// HAT Wert
//
// 0 = CENTER
// 1 = UP
// 2 = UP-RIGHT
// 3 = RIGHT
// 4 = DOWN-RIGHT
// 5 = DOWN
// 6 = DOWN-LEFT
// 7 = LEFT
// 8 = UP-LEFT
// =====================================

uint8_t HatSwitch_Get()
{
    bool up = (hatState[0] == LOW);
    bool right = (hatState[1] == LOW);
    bool down = (hatState[2] == LOW);
    bool left = (hatState[3] == LOW);

    // =================================
    // CENTER
    // =================================

    if(
        !up &&
        !right &&
        !down &&
        !left
    )
    {
        return 0;
    }

    // =================================
    // UP
    // =================================

    if(
        up &&
        !right &&
        !down &&
        !left
    )
    {
        return 1;
    }

    // =================================
    // UP-RIGHT
    // =================================

    if(
        up &&
        right &&
        !down &&
        !left
    )
    {
        return 2;
    }

    // =================================
    // RIGHT
    // =================================

    if(
        right &&
        !up &&
        !down &&
        !left
    )
    {
        return 3;
    }

    // =================================
    // DOWN-RIGHT
    // =================================

    if(
        down &&
        right &&
        !up &&
        !left
    )
    {
        return 4;
    }

    // =================================
    // DOWN
    // =================================

    if(
        down &&
        !up &&
        !right &&
        !left
    )
    {
        return 5;
    }

    // =================================
    // DOWN-LEFT
    // =================================

    if(
        down &&
        left &&
        !up &&
        !right
    )
    {
        return 6;
    }

    // =================================
    // LEFT
    // =================================

    if(
        left &&
        !up &&
        !right &&
        !down
    )
    {
        return 7;
    }

    // =================================
    // UP-LEFT
    // =================================

    if(
        up &&
        left &&
        !right &&
        !down
    )
    {
        return 8;
    }

    // =================================
    // Ungültige Kombination
    // =================================

    return 0;
}