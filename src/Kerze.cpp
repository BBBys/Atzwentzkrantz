#include <Arduino.h>
#include "Kerze.h"
Kerze::Kerze(uint8_t nr, uint8_t start, uint8_t laenge, bool brennt, Adafruit_NeoPixel pixels)
{
    Pixels=pixels;
    Brennt = brennt;
    Laenge = laenge;
    Start = start;
    Nr = nr;
    Stand = 100;
    Brennt = false;
    cROT = Pixels.Color(255, 0, 0);
       cGELB = Pixels.Color(255, 255, 0);
}
void Kerze::Paint()
{
    uint8_t bl, i;
    bl = (uint8_t)0.01 * (float)Laenge *(float) Stand; 
/*
    if (Brennt)
    {
        bl -= Flamme;
        i = Start + Laenge + Laenge - Flamme;
        Pixels.fill(cGELB, i, Flamme);
    }
    Pixels.fill(cROT, Start, bl);
    Pixels.fill(cROT, Start + Laenge, bl);
    Pixels.fill(cROT, Start + Laenge + Laenge, bl);
    */
}