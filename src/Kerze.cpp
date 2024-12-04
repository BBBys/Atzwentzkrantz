#include <Arduino.h>
#include "Kerze.h"
Kerze::Kerze(uint8_t nr, uint8_t start, uint8_t laenge, bool brennt)
{
    Brennt = brennt;
    Laenge = laenge;
    Start = start;
    Nr = nr;
    Stand = 100.0;
    Brennt = false;
    log_d("Kerze %d OK", Nr);
}
void Kerze::Brennen(unsigned long zeit)
{
    if (Brennt)
        Stand = 100.0 * (1.0 - (double)zeit / (double)MAXBRENNZEIT);
    assert(Stand > 0.0);
}

void Kerze::Paint(Adafruit_NeoPixel *Pixels)
{
    const uint32_t cROT = Pixels->Color(255, 0, 0),
                   cGELB = Pixels->Color(255, 255, 0);
    uint8_t nRot, richtg;

    log_d("%d. Kerze Start %d Länge %d Stand %f %%", Nr, Start, Laenge, Stand);
    nRot = (uint8_t)(0.01 * (float)Laenge * (float)Stand);
    assert(Start + 2 * Laenge + nRot <= 120);

    if (Brennt)
    {
        nRot -= Flamme;
    }

    log_d("Länge aktuell %d", nRot);

    richtg = Nr % 2;
    uint8_t pos[] = {
        Start,
        Start + Laenge + Laenge - nRot,
        Start + Laenge + Laenge - nRot - (Brennt ? Flamme : 0),
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
            Pixels->fill(cGELB, pos[2], Flamme);
        Pixels->fill(cROT, pos[3], nRot);
    }
    else // erste Reihe umgekehrt
    {
        Pixels->fill(cROT, pos[4], nRot);
        Pixels->fill(cROT, pos[5], nRot);
        if (Brennt)
            Pixels->fill(cGELB, pos[6], Flamme);
        assert(Start + 3 * Laenge - nRot + nRot <= 120);
        Pixels->fill(cROT, pos[7], nRot);
    }

    log_d("Kerze fertig");
}
