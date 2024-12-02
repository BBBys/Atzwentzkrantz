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
Kerze *Kerzen[4];
void setup()
{
  uint8_t adventNummer,start;
  log_i("Start...");
  adventNummer=Datum();
  log_d("%d. Advent",adventNummer);
  start = 0;
  log_d("Kerzen");
  for (u_int8_t i = 0; i < NKERZEN; i++)
  {
    bool brennt = (i + 1) >= adventNummer;
    Kerzen[i] = new Kerze(0, start, NPXKERZE, brennt,pixels);
  start += NPXKERZE;
  }
    log_i("...setup");
}
void loop() {
  log_d("Paint");
  for (uint8_t i = 0; i < NKERZEN; i++)
  {
    Kerzen[i]->Paint();
  }
  pixels.show();
  delay(60000l);
}
