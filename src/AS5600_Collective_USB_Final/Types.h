#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>

// =================================================
// System Status
// =================================================

enum SystemStatus
{
    STATUS_ERROR,
    STATUS_OK,
    STATUS_CALIBRATION
};


// =================================================
// Calibration Data
// =================================================

struct CalibrationData
{
    uint32_t magic;
    uint16_t zMin;
    uint16_t zMax;
    uint16_t rxMin;
    uint16_t rxMax;
};

// =================================================
// Controller State
// =================================================

struct ControllerState
{
    int8_t z;
    int8_t rx;
    uint16_t buttons;
    uint8_t hat;
};
#endif