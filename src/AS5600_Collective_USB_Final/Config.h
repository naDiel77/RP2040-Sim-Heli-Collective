#ifndef CONFIG_H
#define CONFIG_H

// =================================================
// Firmware
// =================================================

#define FW_NAME    "AS5600 Collective USB"
#define FW_VERSION "V6.0 Final"

// =================================================
// GPIO -> FIX! Do not change!
// =================================================

#define SDA_PIN 14
#define SCL_PIN 15
#define RX_PIN 26
#define RGB_PIN 16
#define RGB_COUNT 1
#define CALIBRATION_BUTTON 27

// =================================================
// AS5600
// =================================================

#define AS5600_ADDR 0x36
#define RAW_ANGLE_H 0x0C
#define STATUS_REG  0x0B
#define INVERT_Z false

// =================================================
// Calibration (Time = 10s)
// =================================================

#define CALIBRATION_TIME 10000

// =================================================
// EEPROM
// =================================================

#define EEPROM_SIZE 64
#define EEPROM_MAGIC 0x56

// =================================================
// Alpha-Beta Filter -> can adjust
// =================================================

#define FILTER_ALPHA 0.25f
#define FILTER_BETA  0.05f

// =================================================
// Options --> uncommand if needed
// =================================================

//#define INVERT_Z  false
//#define INVERT_RX false

#endif