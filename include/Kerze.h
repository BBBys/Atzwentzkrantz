#pragma once
#ifndef _KERZE_H_
#define _KERZE_H_
#include <Adafruit_NeoPixel.h>
static const u_int8_t NEOPIXELPIN = 0,NKERZEN=4;
class Kerze
{
private:
   static  Adafruit_NeoPixel Pixels;
    static uint32_t cROT, cGELB;
    static const uint8_t Flamme = 3;
    uint8_t Laenge, Nr, Start, Stand;
    bool Brennt;
public:
    Kerze(uint8_t nr, uint8_t start, uint8_t laenge, bool brennt,Adafruit_NeoPixel pixels);
    ~Kerze();
    void Paint();
};
//Kerze::~Kerze(){}

#endif