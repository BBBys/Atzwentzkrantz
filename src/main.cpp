#include <Arduino.h>
#include "AKranz.h"
#include "Kerze.h"
Kerze Kerzen[4];
void setup()
{
  uint8_t start = 0;
  Kerzen[0] = new Kerze(0, start,NPXKERZE);
  start += NPXKERZE;
  Kerzen[1] = new Kerze(1, start);
  start += NPXKERZE;
  Kerzen[2] = new Kerze(2, start);
  start += NPXKERZE;
  Kerzen[3] = new Kerze(3, start);
}

void loop() {
}
