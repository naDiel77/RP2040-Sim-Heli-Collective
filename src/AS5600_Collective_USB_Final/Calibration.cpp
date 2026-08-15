#include "Calibration.h"
#include "Config.h"
#include "EEPROM.h"
#include "AS5600.h"
#include "StatusLED.h"
#include "ZAxis.h"
#include "RXAxis.h"

extern CalibrationData cal;
extern CalibrationData cal;
static bool running=false;
static uint32_t startTime;
extern CalibrationData cal;

void Calibration_Init()
{
    pinMode(
        CALIBRATION_BUTTON,
        INPUT_PULLUP
    );
}

void Calibration_Start()
{
    running = true;
    startTime = millis();
    cal.zMin = 4095;
    cal.zMax = 0;
    cal.rxMin = 4095;
    cal.rxMax = 0;
    setStatus(STATUS_CALIBRATION);
}

void Calibration_Update()
{
    if(!running)
        return;
    uint16_t raw;

    if(readAS5600(raw))
    {
        if(raw < cal.zMin)
            cal.zMin=raw;
        if(raw > cal.zMax)
            cal.zMax=raw;
    }

    uint16_t rxRaw;

    rxRaw = analogRead(RX_PIN);
    if(rxRaw < cal.rxMin)
        cal.rxMin = rxRaw;
    if(rxRaw > cal.rxMax)
        cal.rxMax = rxRaw;

    if(millis() - startTime >= CALIBRATION_TIME)
      {
      running = false;
      saveCalibration(cal);
      ZAxis_SetCalibration(
          cal.zMin,
          cal.zMax
      );

      RXAxis_SetCalibration(
          cal.rxMin,
          cal.rxMax
      );

      setStatus(STATUS_OK);
      }

}

bool Calibration_Running()
{
    return running;
}