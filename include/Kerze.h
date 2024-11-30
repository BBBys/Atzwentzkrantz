#pragma once
#ifndef _KERZE_H_
#define _KERZE_H_
class Kerze
{
private:
    uint8_t Länge,Nr,Start;

public:
    Kerze(uint8_t nr,uint8_t start,uint8_t länge);
    ~Kerze();
};
Kerze::~Kerze()
{
}

#endif