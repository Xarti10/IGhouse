#include "WiFiService.hpp"

#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include <Utils/PreferenceAdapter.hpp>

namespace IGHouse
{
namespace Connection
{

TaskHandle_t WiFiService::connectionTaskHandler = nullptr;

WiFiService::WiFiService(TaskHandle_t &taskHandle)
: ssid("")
, password("")
{
    connectionTaskHandler = taskHandle;
    // Setup callback function for successful connection
    WiFi.onEvent(gotIP, SYSTEM_EVENT_STA_GOT_IP);
    // Setup callback function for lost connection
    WiFi.onEvent(lostCon, SYSTEM_EVENT_STA_DISCONNECTED);
}

void WiFiService::gotIP(system_event_id_t event) {
//    isConnected = true;
//    connStatusChanged = true;
    xTaskNotify(connectionTaskHandler, 0x04, eSetBits);
}

void WiFiService::lostCon(system_event_id_t event) {
//    isConnected = false;
//    connStatusChanged = true;
    xTaskNotify(connectionTaskHandler, 0x03, eSetBits);
}

void WiFiService::connectWiFi()
{
    WiFi.disconnect(true);
    WiFi.enableSTA(true);
    WiFi.mode(WIFI_STA);

    Serial.println();
    Serial.print("Start connection to ");

    Serial.println(ssid);
    WiFi.begin(ssid.c_str(), password.c_str());
}

bool WiFiService::getNewPreferences()
{
    WiFiPreferences wifiPrefs = PreferencesAdapter::getWiFiPreferences();
    Serial.println();
    if (wifiPrefs.valid)
    {
        if (!wifiPrefs.ssid.equals("") || !wifiPrefs.password.equals(""))
        {
            Serial.println("Read from preferences:");
            Serial.println("SSID: " + wifiPrefs.ssid + " password: " + wifiPrefs.password);
            return true;

        }
        Serial.println("Found preferences but credentials are invalid");
    }

    Serial.println("Could not find preferences, need send data over BLE");
    return false;

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