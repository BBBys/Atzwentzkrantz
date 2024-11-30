#include <Arduino.h>
#include "Kerze.h"
Kerze::Kerze(uint8_t nr,uint8_t start,uint8_t länge)
{
    Länge = länge;
    Start = start;
    Nr = nr;
}