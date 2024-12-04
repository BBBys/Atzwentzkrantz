#pragma once
#ifndef _KERZE_H_
#define _KERZE_H_
#include <Adafruit_NeoPixel.h>
static const u_int8_t NEOPIXELPIN = 0,NKERZEN=4;
class Kerze
{
private:
   static const uint8_t Flamme = 3;
   uint8_t Nr, Start;
   // rohe Länge der Kerze
    uint8_t Laenge;
   // Prozent Kerze noch nicht abgebrannt
   float Stand;
   // abgebrannte Länge in %
   uint8_t Bl;
   bool Brennt;
   public:
   Kerze(uint8_t nr, uint8_t start, uint8_t laenge, bool brennt);
   void Brennen(unsigned long zeit);
    ~Kerze();
    void Paint(Adafruit_NeoPixel *pixels);
};
//Kerze::~Kerze(){}

#endif