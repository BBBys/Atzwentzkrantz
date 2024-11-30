#pragma once
#include <Arduino.h>
#ifndef _AKRANZ_H_
#define _AKRANZ_H_
const uint8_t NPX = 120;
const uint8_t NPXKERZE = NPX/12;
void setup();
void loop();
uint8_t Datum();
#endif