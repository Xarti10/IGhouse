#include "WiFiService.hpp"

#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>

namespace IGHouse
{
namespace Connection
{
namespace
{

void gotIP(system_event_id_t event) {
//    isConnected = true;
//    connStatusChanged = true;
}

void lostCon(system_event_id_t event) {
//    isConnected = false;
//    connStatusChanged = true;
}

}//namespace


void WiFiService::connectWiFi()
{
    // Setup callback function for successful connection
    WiFi.onEvent(gotIP, SYSTEM_EVENT_STA_GOT_IP);
    // Setup callback function for lost connection
    WiFi.onEvent(lostCon, SYSTEM_EVENT_STA_DISCONNECTED);

    WiFi.disconnect(true);
    WiFi.enableSTA(true);
    WiFi.mode(WIFI_STA);

    Serial.println();
    Serial.print("Start connection to ");

    Serial.println(ssid);
    WiFi.begin(ssid.c_str(), password.c_str());
}

void WiFiService::getPreferences()
{
    Preferences preferences;
    preferences.begin("WiFiCred", false);
    bool hasPref = preferences.getBool("valid", false);
    if (hasPref)
    {
        ssid = preferences.getString("ssid","");
        password = preferences.getString("password","");

        if (ssid.equals("") || password.equals(""))
        {
            Serial.println("Found preferences but credentials are invalid");
        }
        else {
            Serial.println("Read from preferences:");
            Serial.println("SSID: " + ssid + " password: " + password);
//            hasCredentials = true;
        }
    }
    else
    {
        Serial.println("Could not find preferences, need send data over BLE");
    }
    preferences.end();
}

bool WiFiService::scanWiFi()
{
    Serial.println("Start scanning for networks");

    WiFi.disconnect(true);
    WiFi.enableSTA(true);
    WiFi.mode(WIFI_STA);

    // Scan for AP
    int apNum = WiFi.scanNetworks(false,true,false,1000);
    if (apNum == 0) {
        Serial.println("Found no networks?????");
        return false;
    }

    bool ssidFound = false;

    for (int index=0; index<apNum; index++) {
        String ssidVal = WiFi.SSID(index);
        Serial.println("Found AP: " + ssidVal + " RSSI: " + WiFi.RSSI(index));
        if (!strcmp((const char*) &ssidVal[0], (const char*) &ssid[0])) {
            Serial.println("Found primary AP");
            ssidFound = true;
        }
    }

    return ssidFound;
}

}//namespace Connection
}//namespace IGHouse