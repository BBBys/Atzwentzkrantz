#include <Arduino.h>
#include "Kerze.h"
Kerze::Kerze(uint8_t nr,uint8_t start,uint8_t länge)
{
    Länge = länge;
    Start = start;
    Nr = nr;
    Stand = 100;
    Brennt = false;
}
void Kerze::Paint() 
{ 
    uint8_t bl;
    bl = 0.01 * (float)(Länge * Stand);     // prüfen auf Überlauf!
    if (Brennt)
        bl -= 3;

    for (size_t i = 0; i < bl; i++)
    {
        pixels.setPixelColor(Start + i, pixels.Color(255, 0,0));
        pixels.setPixelColor(Start + i + Länge, pixels.Color(255, 0, 0));
        pixels.setPixelColor(Start + i + Länge + Länge, pixels.Color(255, 0, 0));
    }
    }