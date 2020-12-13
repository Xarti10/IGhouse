#include "DeviceCallbackHandler.hpp"

#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"

#include <memory>
#include <cstdint>
#include <map>
#include "Arduino.h"
#include "Utils/CommandDefinitions.hpp"


namespace IGHouse
{
namespace Connection
{
namespace Drv
{
namespace Bluetooth
{

namespace
{

std::map<String, Command> stringToCommandMap
    {
        {"erase",               Command::ERASE},
        {"connectToWiFi",       Command::CONNECT_TO_WIFI},
        {"getSensorData",       Command::GET_SENSOR_DATA},
        {"reset",               Command::RESET}
    };

Command translateStringToCommand(String commandString)
{
    auto command = stringToCommandMap.find(commandString);
    if(command != stringToCommandMap.end())
        return command->second;
    else
        return Command::UNKNOWN;
}

}//namespace

DeviceCallbackHandler::DeviceCallbackHandler(char *accessPointName,
                                             std::shared_ptr<BLECharacteristic> &characteristic,
                                             std::uint32_t jsonBufferSize)
        : accessPointName(accessPointName)
        , jsonBuffer(jsonBufferSize)
        , characteristics(characteristic)
{

}

String DeviceCallbackHandler::decodeData(BLECharacteristic *pCharacteristic)
{
    std::string value = pCharacteristic->getValue();
    if (value.length() == 0) {
        return "";
    }
    Serial.println("Received over BLE: " + String((char *)&value[0]));

    // Decode data
    int keyIndex = 0;
    for (char & index : value) {
        index = (char) index ^ (char) accessPointName[keyIndex];
        keyIndex++;
        if (keyIndex >= strlen(accessPointName)) keyIndex = 0;
    }
    return (char *)&value[0];
}

void DeviceCallbackHandler::fillWiFiCredentials(JsonVariant arguments)
{
    JsonVariant ssidFromJson = arguments["ssid"];
    JsonVariant passwordFromJson = arguments["password"];

    if(ssidFromJson.isNull())
    {
        Serial.println("Wrong ssid name was provided");
        return;
    }
    ssid = ssidFromJson.as<String>();
    password = passwordFromJson.isNull() ? "" : passwordFromJson.as<String>();

    Preferences preferences;
    preferences.begin("WiFiCred", false);
    preferences.putString("ssid", ssid);
    preferences.putString("password", password);
    preferences.putBool("valid", true);
    preferences.end();

    Serial.println("Received over bluetooth:");
    Serial.println("primary SSID: " + ssid + " password: " + password);
//    connStatusChanged = true;
//    hasCredentials = true;
}

void DeviceCallbackHandler::eraseWiFiCredentials()
{
    Serial.println("Received erase command");
    Preferences preferences;
    preferences.begin("WiFiCred", false);
    preferences.clear();
    preferences.end();
//    connStatusChanged = true;
//    hasCredentials = false;
    ssid = "";
    password = "";

    int err;
    err = nvs_flash_init();
    Serial.println("nvs_flash_init: " + err);
    err = nvs_flash_erase();
    Serial.println("nvs_flash_erase: " + err);
}

void DeviceCallbackHandler::onWrite(BLECharacteristic *pCharacteristic)
{
    /** Json object for incoming data */
    deserializeJson(jsonBuffer, decodeData(pCharacteristic));
    jsonBuffer.shrinkToFit();

    JsonObject jsonIn = jsonBuffer.as<JsonObject>();
    if (!jsonIn.isNull())
    {
        JsonVariant command = jsonIn["command"];
        if (!command.isNull())
        {
            switch(translateStringToCommand(command.as<String>()))
            {
                case Command::CONNECT_TO_WIFI:
                {
                    JsonVariant arguments = jsonIn["arguments"];
                    if(arguments.isNull())
                    {
                        Serial.println("No arumgents provided, could not connect to WiFi");
                        return;
                    }
                    fillWiFiCredentials(arguments);
                    break;
                }
                case Command::ERASE:
                {
                    eraseWiFiCredentials();
                    break;
                }
                case Command::RESET:
                {
//                    WiFi.disconnect();
                    esp_restart();
                    break;
                }
                case Command::GET_SENSOR_DATA:
                {
                    Serial.println("");
                    break;
                }
                case Command::UNKNOWN:
                    break;
            }
        }
        Serial.println("No command find in JSON");
    }
    else
        Serial.println("Received invalid JSON");

    jsonBuffer.clear();
}

void DeviceCallbackHandler::onRead(BLECharacteristic *pCharacteristic)
{
    Serial.println("BLE onRead request");
    String wifiCredentials;

    /** Json object for outgoing data */
    JsonObject jsonOut = jsonBuffer.as<JsonObject>();
    jsonOut["ssid"] = ssid;
    jsonOut["password"] = password;

    // Convert JSON object into a string
    serializeJson(jsonOut, wifiCredentials);

    // encode the data
    int keyIndex = 0;
    Serial.println("Stored settings: " + wifiCredentials);
    for (char & wifiCredential : wifiCredentials) {
        wifiCredential = (char) wifiCredential ^ (char) accessPointName[keyIndex];
        keyIndex++;
        if (keyIndex >= strlen(accessPointName)) keyIndex = 0;
    }
    characteristics->setValue((uint8_t*)&wifiCredentials[0],wifiCredentials.length());
    jsonBuffer.clear();
}

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse