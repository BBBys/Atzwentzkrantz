#pragma once
#ifndef _KERZE_H_
#define _KERZE_H_
#include <Adafruit_NeoPixel.h>
static const u_int8_t NEOPIXELPIN = 0,NKERZEN=4;
class Kerze
{
private:
    Adafruit_NeoPixel *Pixels;
    static const uint8_t Flamme = 2;
    uint8_t Nr, Start;
    // rohe Länge der Kerze
    uint8_t Laenge;
   // Prozent Kerze noch nicht abgebrannt
   float Stand;
   // abgebrannte Länge in %
   uint8_t Bl;
   bool Brennt;
   public:
       Kerze(uint8_t nr, uint8_t start, uint8_t laenge, Adafruit_NeoPixel *Pixels);
       void Brennen(unsigned long zeit);
       ~Kerze();
       void Paint(Adafruit_NeoPixel *pixels);
       /**
        * @brief Kerze kann auch zum Signalisieren benutzt werden
        * 
        * @param n so viele Pixel an
        */
       void Signal(uint8_t n);
       void Anzuenden();
};
//Kerze::~Kerze(){}

#endif