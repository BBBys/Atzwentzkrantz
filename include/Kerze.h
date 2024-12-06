/**
 * @file Kerze.h
 * @brief Adventskranz-Kerzen
 * @version 1.0
 * @date 6 4 Dez 30 Nov 2024
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @copyright Copyright (c) 2024 B. Borys
 */
#pragma once
#ifndef _KERZE_H_
#define _KERZE_H_
#include <Adafruit_NeoPixel.h>
/**
 * @brief Farben als RGB-Werte
 *
 */
enum RGBFarben
{
    NEOROT = 0xff0000,
    NEOGELB = 0xff5F00,
    NEOGRUEN = 0x00ff00,
    NEOBLAU = 0x0000ff,
    NEOWEISS = 0xffffff
};
constexpr uint8_t NEOPIXELPIN = 0, NKERZEN = 4;
class Kerze
{
private:
    Adafruit_NeoPixel *Pixels;
    static constexpr uint8_t Flamme = 2;
    uint8_t Nr, Start;
    uint8_t Laenge; // Rohe Länge der Kerze
    float Stand;    // Prozent Kerze noch nicht abgebrannt
    uint8_t Bl;     // Abgebrannte Länge in Pixel
    bool Brennt;
public:
    Kerze(uint8_t nr, uint8_t start, uint8_t laenge, Adafruit_NeoPixel *Pixels)
        : Nr(nr), Start(start), Laenge(laenge), Stand(100.0), Bl(0), 
        Brennt(false), Pixels(Pixels)
    {
        Pixels->fill(0, Start, 3 * laenge);
        log_d("Kerze %d OK", Nr);
    }
    ~Kerze() {}
    void Brennen(unsigned long zeit);
    void Paint();
    /**
     * @brief Kerze kann auch zum Signalisieren benutzt werden
     * @param n so viele Pixel an
     */
    void Signal(uint8_t n);
    void Anzuenden();
};
// Kerze::~Kerze(){}

#endif