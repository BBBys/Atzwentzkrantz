/**
 * @file Datum.cpp
 * @brief Adventskranz - Funktion, um den vierten Sonntag vor dem 25. Dezember
 * zu berechnen
 * @version 1.0
 * @date 2 Dez 30 Nov 2024
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @copyright Copyright (c) 2024 B. Borys
 */
#include <Arduino.h>
#include "AKranz.h"
#include <iostream>
#include <ctime>
#include <WiFi.h>
#include <time.h>
#define TSERVER "192.168.1.1"
#define TZONE "CET-1CEST,M3.5.0/02,M10.5.0/03"
/**
 * @brief auf welchen Tag fällt der 1. Advent object
 * 
 * @param Jahr in UNIX-Zählung (ab 1970)
 * @return std::tm 
 */
std::tm TagErsterAdvent(int year)
{
    uint8_t tag25Dezember, bisSonntag, bis25Dezember;
    std::tm tm25Dezember = {};
    tm25Dezember.tm_year = year; // UNIX-Jahr, zählt ab 1900
    tm25Dezember.tm_mon = 11;    // Dezember ist der 12. Monat (indexiert ab 0)
    tm25Dezember.tm_mday = 25;
    tm25Dezember.tm_hour = 12; // Vermeidung von Problemen mit Sommerzeitumstellungen
    // Berechne den Wochentag (0 = Sonntag, 1 = Montag, ...)
    std::mktime(&tm25Dezember);
    tag25Dezember = tm25Dezember.tm_wday;
    // Berechne die Differenz zum Sonntag
    bisSonntag = (tag25Dezember == 0) ? 0 : 7 - tag25Dezember;
    // Addiere die Tage bis zum nächsten Sonntag und weitere 21 Tage, um zum 4. Sonntag zurückzukehren
    bis25Dezember = bisSonntag + 21;
    // Datum des ersten Advents berechnen
    std::tm tag1Advent = tm25Dezember;
    tag1Advent.tm_mday -= bis25Dezember;
    std::mktime(&tag1Advent);
    log_d("Tage bis Weihnachten %d", bis25Dezember);
    log_d("Tag 1. Advent %d", tag1Advent);
    return tag1Advent;
}
/**
 * @brief der wievielte Advent war schon?
 * 
 * @return * uint8_t Nummer (1...4)
 */
uint8_t Datum()
{
    char buffer[80];
    // time_t enthält die Anzahl der Sekunden seit dem 1.1.1970 0 Uhr
    time_t unixSekunden = 0, t;
    std::tm *jetzt, ersterAdv, Zeit;
    configTzTime(TZONE, TSERVER);
    WiFi.enableIpV6();
    WiFi.begin(WLANSSID, WLANPWD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(2000);
        log_w("Wifi?");
    }
    log_i("Wifi OK");
    //    WiFi.disconnect();
    while (unixSekunden < 4000)
    {
        delay(15010);
        // es dauert etwa 30 s, bis die Zeit stimmt
        // aktuelle Zeit lesen
        log_w("Zeit?");
        time(&unixSekunden);
    }
    WiFi.disconnect(true);// Strom sparen
    // localtime_r -> Zeit in die lokale Zeitzone setzen
    t = std::time(nullptr);
    jetzt = std::localtime(&t);
//    localtime_r(&unixSekunden, &Zeit);
    //strftime(buffer, sizeof(buffer), "&etzt: %Y-%m-%d", &jetzt);
    //log_d("%s", buffer);
    strftime(buffer, sizeof(buffer), "jetzt: %Y-%m-%d", jetzt);
    log_d("%s", buffer);
    ersterAdv = TagErsterAdvent(jetzt->tm_year); // UNIX-Jahr, zählt ab 1900
    strftime(buffer, sizeof(buffer), "1. Advent am %Y-%m-%d", &ersterAdv);
    log_d("%s", buffer);
    return (jetzt->tm_yday - ersterAdv.tm_yday)/7+1;
}