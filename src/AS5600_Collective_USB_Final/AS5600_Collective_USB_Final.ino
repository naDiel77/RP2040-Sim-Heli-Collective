#include <Arduino.h>

#include <Adafruit_TinyUSB.h>

#include "Config.h"
#include "Types.h"
#include "AS5600.h"
#include "ZAxis.h"
#include "RXAxis.h"
#include "StatusLED.h"
#include "Calibration.h"
#include "EEPROM.h"
#include "Buttons.h"
#include "Buttons.h"
#include "HatSwitch.h"

// =================================================
// Global Data
// =================================================

CalibrationData cal;
ControllerState controller;
bool calibrationAtBoot = false;
static uint16_t rxMin = 49;
static uint16_t rxMax = 978;

// =================================================
// USB HID
// =================================================

uint8_t const desc_hid_report[] =
{
    TUD_HID_REPORT_DESC_GAMEPAD()
};


Adafruit_USBD_HID usb_hid;
hid_gamepad_report_t gp;

// =================================================
// USB INIT
// =================================================

void USB_Init()
{
    if(!TinyUSBDevice.isInitialized())
        TinyUSBDevice.begin(0);
        usb_hid.setPollInterval(2);
        usb_hid.setReportDescriptor(
            desc_hid_report,
            sizeof(desc_hid_report)
        );

    usb_hid.begin();

    if(TinyUSBDevice.mounted())
    {
        TinyUSBDevice.detach();
        delay(10);
        TinyUSBDevice.attach();
    }
}

// =================================================
// SETUP
// =================================================

void setup()
{
    StatusLED_Init();
    setStatus(STATUS_ERROR);
    Buttons_Init();
    EEPROM_Init();
    Calibration_Init();
    calibrationAtBoot = (digitalRead(CALIBRATION_BUTTON)==LOW);
    if(calibrationAtBoot)
    {
        Calibration_Start();
    }
    else
    {
        if(loadCalibration(cal))
        {
            ZAxis_SetCalibration(
                cal.zMin,
                cal.zMax
            );
            RXAxis_SetCalibration(
                cal.rxMin,
                cal.rxMax
            );
        }
    }

    USB_Init();

    if(AS5600_Init())
    {
        if(calibrationAtBoot)
        {
            setStatus(
                STATUS_CALIBRATION
            );
        }
        else
        {
            setStatus(STATUS_OK);
        }

    }
    else
    {
        setStatus(STATUS_ERROR);
    }

    RXAxis_Init();
}

// =================================================
// LOOP
// =================================================
void loop()
{
    Buttons_Update();
    HatSwitch_Update();
    Calibration_Update();
    uint16_t raw;
    if(readAS5600(raw))
    {
        controller.z = updateZAxis(raw);
        gp.z = controller.z;
       if(usb_hid.ready())
        {
            gp.buttons = 0;
            for(uint8_t i = 0; i < BUTTON_COUNT; i++)
            {
                if(Button_Pressed(i))
                {
                    gp.buttons |= (1 << i);
                }
            }
            gp.hat = HatSwitch_Get();
            usb_hid.sendReport(
                0,
                &gp,
                sizeof(gp)
            );
        }
    }
    int8_t rx;
    rx = updateRXAxis();
    gp.rx = rx;
    rx = updateRXAxis();
    gp.rx = rx;

    if(usb_hid.ready())
    {
        usb_hid.sendReport(
            0,
            &gp,
            sizeof(gp)
        );
    }
    delay(2);
}