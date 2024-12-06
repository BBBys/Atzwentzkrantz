#include <Arduino.h>
#include "Kerze.h"
Kerze::Kerze(uint8_t nr, uint8_t start, uint8_t laenge, Adafruit_NeoPixel *pixels)
{
    Pixels = pixels;
    Brennt = false;
    Laenge = laenge;
    Start = start;
    Nr = nr;
    Stand = 100.0;
    Brennt = false;
    Pixels->fill(0, Start, 3 * laenge);
    log_d("Kerze %d OK", Nr);
}
void Kerze::Anzuenden()
{
    Brennt = true;
}
void Kerze::Signal(uint8_t n)
{
    if (n < 1)
        Pixels->fill(0, Start, 3 * Laenge);
    else
        Pixels->fill(Pixels->Color(32, 64, 0), Start, n);
    Pixels->show();
}
/**
 * @brief Abbrennen simulieren
 *
 * @param zeit
 */
void Kerze::Brennen(unsigned long zeit)
{
    if (Brennt)
    {
        Stand = 100.0 * (1.0 - (double)zeit / (double)MAXBRENNZEIT);
        log_d("brennt %d von %d = %f %%", zeit, MAXBRENNZEIT, Stand);
        if (Stand < 0.1) // Brennschluss und verhindern, dass Stand negativ wird
        {
            Brennt = 0;
            Stand = 0.0;
        }
    }
    else
        log_d("brennt nicht");
}

void Kerze::Paint(Adafruit_NeoPixel *Pixels)
{
    const uint32_t cROT = Pixels->Color(90, 0, 0),
                   cGELB = Pixels->Color(255, 255, 0);
    uint8_t nRot, richtg;

    log_d("%d. Kerze Start %d Länge %d Stand %.0f %%", Nr, Start, Laenge, Stand);
    nRot = (uint8_t)(0.01 * (float)Laenge * (float)Stand);
    assert(Start + 2 * Laenge + nRot <= 120);

    if (Brennt)
    {
        nRot -= Flamme;
    }

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
    log_d("Kerze fertig");
}
