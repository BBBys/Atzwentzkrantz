/**
 * @file Kerze.cpp
 * @brief eine Adventskranz-Kerze
 * @version 1.0
 * @date 6 4 Dez 30 Nov 2024
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @copyright Copyright (c) 2024 B. Borys
 */
#include <Arduino.h>
#include "Kerze.h"
void Kerze::Anzuenden() 
{
    Brennt = true;
}
void Kerze::Signal(uint8_t n)
{
    if (n < 1)
        Pixels->fill(0, Start, 3 * Laenge);
    else
        Pixels->fill(NEOGRUEN, Start, n);
    Pixels->show();
}
/**
 * @brief Abbrennen simulieren
 * @param zeit wie lange schon in ms
 */
void Kerze::Brennen(unsigned long zeit)
{
    if (!Brennt)
    {
        log_d("brennt nicht");
        return;
    }

    Stand = 100.0 * (1.0 - static_cast<double>(zeit) / MAXBRENNZEIT);
    log_d("brennt %d von %d = %f %%", zeit, MAXBRENNZEIT, Stand);

    if (Stand < 0.1) // Brennschluss und verhindern, dass Stand negativ wird
    {
        Brennt = false;
        Stand = 0.0;
    }
}

/**
 * @brief Kerze zeichnen
 * jede Kerze hat 3 Streifen mit 10 Neopixeln.
 * die Streifen sind in abwechselnden Richtungen geklebt 
 * - vereinacht das Löten, aber erschwert die Programmierung
 * @param Pixels 
 */
void Kerze::Paint()
{
    // dunkles Rot
    const uint32_t cROT = Pixels->Color(90, 0, 0);
    // volles Gelb
    const uint32_t cGELB = NEOGELB;
    uint8_t nRot, richtg;
    log_d("%d. Kerze Start %d Länge %d Stand %.0f %%", Nr, Start, Laenge, Stand);
    nRot = (uint8_t)(0.01 * (float)Laenge * (float)Stand);
    assert(Start + 2 * Laenge + nRot <= 120);
    // ein paar Pixel für die Flamme
    if (Brennt)     nRot -= Flamme;
    log_d("Länge aktuell %d", nRot);
    if (nRot < 1)
    {
        log_w("Kerze abgebrannt, das sollte nicht passieren!!");
        return;
    }
    // in welcher Richtung sind die Streifen aufgeklebt?
    richtg = Nr % 2;
    int pos[] = {
        Start,
        Start + Laenge + Laenge - nRot,
        Start + Laenge + Laenge - nRot - Flamme,
        Start + Laenge + Laenge,
        Start + Laenge - nRot,
        Start + Laenge,
        Start + Laenge + nRot,
        Start + 3 * Laenge - nRot};
    if (richtg == 0) // erste Reihe von unten nach oben
    {
        Pixels->fill(cROT, pos[0], nRot);
        Pixels->fill(cROT, pos[1], nRot);
        if (Brennt)
        {
            Pixels->fill(cGELB, pos[2], Flamme);
            log_d("Flamme Pixel %d...%d", pos[2], pos[2]+1);
        }
        Pixels->fill(cROT, pos[3], nRot);
    }
    else // erste Reihe umgekehrt
    {
        Pixels->fill(cROT, pos[4], nRot);
        Pixels->fill(cROT, pos[5], nRot);
        if (Brennt)
        {
            Pixels->fill(cGELB, pos[6], Flamme);
            log_d("Flamme Pixel %d...%d", pos[6], pos[6]+1);
        }
        assert(Start + 3 * Laenge - nRot + nRot <= 120);
        Pixels->fill(cROT, pos[7], nRot);
    }
    //log_d("Kerze fertig");
}
