/**
 * @file main.cpp
 * @brief Adventskranz
 * @version 0.1
 * @date 4 Dez 30 Nov 2024
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @copyright Copyright (c) 2024 B. Borys
 */ \
#include<Arduino.h>
#include "AKranz.h"
#include "Kerze.h"
Adafruit_NeoPixel pixels(NPX, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
Kerze *Kerzen[4];
unsigned long Letzte = 0;
void setup()
{
  uint8_t adventNummer, start;
  log_i("Start...");
  adventNummer = Datum();
  log_d("%d. Advent", adventNummer);
  start = 0;
  for (u_int8_t i = 0; i < NKERZEN; i++)
  {
    log_d("Kerze %d", i);
    bool brennt = (i + 1) >= adventNummer;
    Kerzen[i] = new Kerze(i, start, NPXKERZE, brennt);
    start += 3*NPXKERZE;
  }
  log_i("...setup");
}
void loop()
{
  if (millis() - Letzte > INTERVALL)
  {
    
    for (uint8_t i = 0; i < NKERZEN; i++)
    {
      log_d("Paint %d",i);
      Kerzen[i]->Brennen(millis());
      Kerzen[i]->Paint(&pixels);
    }
    pixels.show();
    Letzte = millis();
  }
  delay(4990l);
}
