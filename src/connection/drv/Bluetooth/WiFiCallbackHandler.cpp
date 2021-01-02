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
#include "Utils/PreferenceAdapter.hpp"
#include "CipherAES.h"
#include "FreeRTOS.h"


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

WiFiCallbackHandler::WiFiCallbackHandler(std::shared_ptr<CipherAES> &cipher,
                                         TaskHandle_t &taskHandle,
                                         std::uint16_t jsonBufferSize)
: CharacteristicCallbackHandler(cipher)
, connectionTaskHandler(taskHandle)
, jsonBuffer(jsonBufferSize)
{
}

void WiFiCallbackHandler::fillWiFiCredentials()
{
    Serial.println(__FUNCTION__);
    JsonVariant ssidFromJson = jsonBuffer["arguments"][0]["ssid"];
    JsonVariant passwordFromJson = jsonBuffer["arguments"][0]["password"];

    if(ssidFromJson.isNull())
    {
        Serial.println("Wrong ssid name was provided");
        return;
    }
    WiFiPreferences wifiPrefs;
    wifiPrefs.ssid = ssidFromJson.as<String>();
    wifiPrefs.password = passwordFromJson.isNull() ? "" : passwordFromJson.as<String>();
    wifiPrefs.valid = true;
    PreferencesAdapter::setWiFiPreferences(wifiPrefs);

    Serial.println("Received over bluetooth:");
    Serial.println("primary SSID: " +  wifiPrefs.ssid + " password: " + wifiPrefs.password);
    xTaskNotify(connectionTaskHandler, 0x01, eSetBits);

}

void WiFiCallbackHandler::eraseWiFiCredentials()
{
    Serial.println(__FUNCTION__);
    Serial.println("Received erase command");

    PreferencesAdapter::eraseWiFiPreferences();

    xTaskNotify(connectionTaskHandler, 0x02, eSetBits);
}

void WiFiCallbackHandler::onWrite(BLECharacteristic *pCharacteristic)
{
    Serial.println(__FUNCTION__);
    /** Json object for incoming data */
    Serial.println("On write request");
    deserializeJson(jsonBuffer, decodeData(pCharacteristic));
    Serial.print("Translated Json: ");
    Serial.println(jsonBuffer.as<String>());

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
                    fillWiFiCredentials();
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

    auto wifiPrefs = PreferencesAdapter::getWiFiPreferences();

    jsonBuffer["ssid"] = wifiPrefs.ssid;
    jsonBuffer["password"] = wifiPrefs.password;

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