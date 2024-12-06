/**
 * @file main.cpp
 * @brief Adventskranz
 * @version 0.1
 * @date 6 4 Dez 30 Nov 2024
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @copyright Copyright (c) 2024 B. Borys
 */
#include <Arduino.h>
#include "AKranz.h"
#include "Kerze.h"
Adafruit_NeoPixel pixels(NPX, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);
Kerze *Kerzen[NKERZEN];
unsigned long Startzeit, Letzte = 0;
void setup()
{
  uint8_t adventNummer,i, start = 0;
  log_i("Start...");
  pixels.clear();
  pixels.show();
  for (i = 0; i < NKERZEN; i++)
  {
    log_d("anlegen Kerze %d", i);
    Kerzen[i] = new Kerze(i, start, NPXKERZE, &pixels);
    start += 3 * NPXKERZE; // jede Kerze ist 3 Streifen lang
  }
  adventNummer = Datum();
#ifndef NDEBUG
  adventNummer++; // zum Testen eine Kerze mehr anzünden
#endif
  log_d("es ist der %d. Advent", adventNummer);
  for (i = 0; i < adventNummer; i++)
  {
    log_d("anzünden Kerze %d", i);
    Kerzen[i]->Anzuenden();
  }
  Startzeit = millis();
  log_i("...setup");
}

void loop()
{
  /**
   * @brief Kerzen animieren
   * in größeren Abständen: Kerzen abbrennen lassen und neu zeichnen
   */
  if (millis() - Letzte > INTERVALL)//Überlauf möglich?
  {
    pixels.clear();
    for (uint8_t i = 0; i < NKERZEN; i++)
    {
      log_d("Paint Kerze %d", i);
      Kerzen[i]->Brennen(millis() - Startzeit);
      Kerzen[i]->Paint();
    }
    pixels.show();
    Letzte = millis();
  }
  /**
   * @brief sonstiges 
   */

  delay(4990l);
}
