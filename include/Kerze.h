#pragma once
#ifndef _KERZE_H_
#define _KERZE_H_
#include <Adafruit_NeoPixel.h>
static const u_int8_t NEOPIXELPIN = 0;
class Kerze
{
private:
    uint8_t Länge,Nr,Start,Stand;
    bool Brennt;
public:
    Kerze(uint8_t nr,uint8_t start,uint8_t länge);
    ~Kerze();
    void Paint();
};
Kerze::~Kerze()
{
}

#endif