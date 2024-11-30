/**
 * @file main.cpp
 * @brief Adventskranz
 * @version 0.1
 * @date 30 Nov 2024 
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @copyright Copyright (c) 2024 B. Borys
 */ \
#include<Arduino.h>
#include "AKranz.h"
#include "Kerze.h"
Adafruit_NeoPixel pixels(NPX, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
Kerze Kerzen[4];
void setup()
{
  uint8_t start = 0;
  Kerzen[0] = new Kerze(0, start,NPXKERZE);
  start += NPXKERZE;
  Kerzen[1] = new Kerze(1, start, NPXKERZE);
  start += NPXKERZE;
  Kerzen[2] = new Kerze(2, start, NPXKERZE);
  start += NPXKERZE;
  Kerzen[3] = new Kerze(3, start, NPXKERZE);
}
void loop() {
  for (size_t i = 0; i < 4; i++)
  {
    Kerzen[i].Paint();
  }
  pixels.show();
}
uint8_t Datum(){}