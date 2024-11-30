/**
 * @file Datum.cpp
 * @brief Adventskranz - Funktion, um den vierten Sonntag vor dem 25. Dezember
 * zu berechnen
 * @version 0.1
 * @date 30 Nov 2024
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @copyright Copyright (c) 2024 B. Borys
 */
#include <Arduino.h>
#include "AKranz.h"
#include <iostream>
#include <ctime>
#include <WiFi.h>
#include <time.h>
#include <NTP.h>
#define Zeitserver "192.168.1.1"
#define Zeitzone "CET-1CEST,M3.5.0/02,M10.5.0/03"

std::tm getFirstAdvent(int year)
{
    uint8_t weekday, daysToSunday, daysBeforeChristmas;
    std::tm christmas = {};
    christmas.tm_year = year; // UNIX-Jahr, zählt ab 1900
    christmas.tm_mon = 11;    // Dezember ist der 12. Monat (indexiert ab 0)
    christmas.tm_mday = 25;
    christmas.tm_hour = 12; // Vermeidung von Problemen mit Sommerzeitumstellungen
    // Berechne den Wochentag (0 = Sonntag, 1 = Montag, ...)
    std::mktime(&christmas);
    weekday = christmas.tm_wday;
    // Berechne die Differenz zum Sonntag
    daysToSunday = (weekday == 0) ? 0 : 7 - weekday;
    // Addiere die Tage bis zum nächsten Sonntag und weitere 21 Tage, um zum 4. Sonntag zurückzukehren
    daysBeforeChristmas = daysToSunday + 21;
    // Datum des ersten Advents berechnen
    std::tm firstAdvent = christmas;
    firstAdvent.tm_mday -= daysBeforeChristmas;
    std::mktime(&firstAdvent);
    log_d("%d", year);
    log_d("%d", weekday);
    log_d("%d", daysBeforeChristmas);
    log_d("%d", firstAdvent);
    return firstAdvent;
}
uint8_t Datum()
{
    char buffer[80];
    // time_t enthält die Anzahl der Sekunden seit dem 1.1.1970 0 Uhr
    time_t aktuelleZeit,t;
    std::tm *now,ersterAdv, Zeit;
    WiFiUDP wifiUdp;
    NTP ntp(wifiUdp); // Parameter für die zu ermittelnde Zeit
    configTzTime(Zeitzone, Zeitserver);
    WiFi.enableIpV6();
    WiFi.begin(WLANSSID, WLANPWD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(2000);
        log_w("Wifi?");
    }
    log_i("Wifi OK");
    ntp.ruleDST("CEST", Last, Sun, Mar, 2, 120);
    ntp.ruleSTD("CET", Last, Sun, Oct, 3, 60);
    ntp.updateInterval(600000L); // 5 Min
    ntp.begin(Zeitserver);
    ntp.update();
    WiFi.disconnect();
    // aktuelle Zeit lesen
    time(&aktuelleZeit);
    // localtime_r -> Zeit in die lokale Zeitzone setzen
    localtime_r(&aktuelleZeit, &Zeit);
    strftime(buffer, sizeof(buffer), "Zeit: %Y-%m-%d", &Zeit);
    log_i("%s",buffer);
    t = std::time(nullptr);
    now = std::localtime(&t);
    strftime(buffer, sizeof(buffer), "now: %Y-%m-%d", now);
    log_i("%s", buffer);
    ersterAdv = getFirstAdvent(now->tm_year); // UNIX-Jahr, zählt ab 1900
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &ersterAdv);
    std::cout << "Der erste Advent ist am " << buffer << std::endl;

    return ersterAdv.tm_yday;
}