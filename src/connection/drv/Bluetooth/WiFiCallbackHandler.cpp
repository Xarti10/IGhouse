#include "WiFiCallbackHandler.hpp"

#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"

#include <memory>
#include <cstdint>
#include <map>
#include "Arduino.h"
#include "Utils/CommandDefinitions.hpp"
#include "Cipher.h"

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

std::map<String, WiFiCommand> stringToCommandMap
    {
        {"erase",         WiFiCommand::ERASE},
        {"connectToWiFi", WiFiCommand::CONNECT_TO_WIFI},
        {"reset",         WiFiCommand::RESET}
    };

WiFiCommand translateStringToCommand(String commandString)
{
    auto command = stringToCommandMap.find(commandString);
    if(command != stringToCommandMap.end())
        return command->second;
    else
        return WiFiCommand::UNKNOWN;
}

}//namespace

WiFiCallbackHandler::WiFiCallbackHandler(std::shared_ptr<Cipher> &cipher,
                                         std::uint16_t jsonBufferSize)
: CharacteristicCallbackHandler(cipher)
, ssid("xxx")
, password("xxxxxx")
, jsonBuffer(jsonBufferSize)
{
}

void WiFiCallbackHandler::fillWiFiCredentials(JsonVariant arguments)
{
    Serial.println(__FUNCTION__);
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

void WiFiCallbackHandler::eraseWiFiCredentials()
{
    Serial.println(__FUNCTION__);
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

void WiFiCallbackHandler::onWrite(BLECharacteristic *pCharacteristic)
{
    Serial.println(__FUNCTION__);
    /** Json object for incoming data */
    Serial.println("On write request");
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
                case WiFiCommand::CONNECT_TO_WIFI:
                {
                    Serial.println("Command CONNECT_TO_WIFI was called");
                    JsonVariant arguments = jsonIn["arguments"];
                    if(arguments.isNull())
                    {
                        Serial.println("No arumgents provided, could not connect to WiFi");
                        return;
                    }
                    fillWiFiCredentials(arguments);
                    break;
                }
                case WiFiCommand::ERASE:
                {
                    Serial.println("Command ERASE was called");
                    eraseWiFiCredentials();
                    break;
                }
                case WiFiCommand::RESET:
                {
                    Serial.println("Command RESET was called");
//                    WiFi.disconnect();
                    esp_restart();
                    break;
                }
                case WiFiCommand::UNKNOWN:
                    break;
            }
        }
        Serial.println("No command find in JSON");
    }
    else
        Serial.println("Received invalid JSON");

    jsonBuffer.clear();
}

void WiFiCallbackHandler::onRead(BLECharacteristic *pCharacteristic)
{
    Serial.println("BLE onRead request");
    String wifiCredentials;

    Preferences preferences;
    preferences.begin("WiFiCred", false);
    ssid = preferences.getString("ssid");
    password = preferences.getString("password");
    preferences.end();

    jsonBuffer["ssid"] = ssid;
    jsonBuffer["password"] = password;

    Serial.print("Stored settings: ");
    Serial.print(jsonBuffer["ssid"].as<String>());
    Serial.println(jsonBuffer["password"].as<String>());

    // Convert JSON into a string
    serializeJson(jsonBuffer, wifiCredentials);

    String encodedString = cipher->encryptString(wifiCredentials);

    pCharacteristic->setValue(std::string(encodedString.c_str()));

    jsonBuffer.clear();
}

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse