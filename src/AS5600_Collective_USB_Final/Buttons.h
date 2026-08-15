#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

#define BUTTON_COUNT 11

void Buttons_Init();

void Buttons_Update();

bool Button_Pressed(uint8_t index);

#endif