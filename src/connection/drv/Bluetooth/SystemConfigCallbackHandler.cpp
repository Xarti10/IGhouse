#include "SystemConfigCallbackHandler.hpp"
#include "CharacteristicCallbackHandler.hpp"

#include "Arduino.h"
#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"
#include <ArduinoJson.h>
#include <Preferences.h>

#include "CipherAES.h"

#include <cstdint>
#include <memory>
#include <Utils/CommandDefinitions.hpp>
#include <Utils/PinDefinitions.hpp>
#include <Utils/PreferenceAdapter.hpp>

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

std::map<String, ThresholdsDefinition> stringToCommandMap
        {
                {"erase",         ThresholdsDefinition::ERASE},
                {"connectToWiFi", ThresholdsDefinition::SET_NEW_THRESHOLDS},
                {"reset",         ThresholdsDefinition::RESET}
        };

ThresholdsDefinition translateStringToCommand(String commandString)
{
    auto command = stringToCommandMap.find(commandString);
    if(command != stringToCommandMap.end())
        return command->second;
    else
        return ThresholdsDefinition::UNKNOWN;
}

}

SystemConfigCallbackHandler::SystemConfigCallbackHandler(std::shared_ptr<CipherAES> &cipher,
                                                         std::shared_ptr<ThresholdSerializer> &thresholdSerializer,
                                                         std::uint16_t jsonBufferSize)
: CharacteristicCallbackHandler(cipher)
, jsonBuffer(jsonBufferSize)
, thresholdSerializer(thresholdSerializer)
{

}

void SystemConfigCallbackHandler::setNewThresholdsSettings(JsonVariant thresholds)
{
    Serial.println(__FUNCTION__);

    JsonVariant soilMoistureJson = thresholds["soilMoisture"];
    JsonVariant humidityJson = thresholds["humidity"];
    JsonVariant lightJson = thresholds["light"];

    if(soilMoistureJson.isNull() || humidityJson.isNull() || lightJson.isNull())
    {
        Serial.println("Wrong ssid name was provided");
        return;
    }

    ThresholdsPreferences thresholdsPrefs;
    thresholdsPrefs.soilMoisture = soilMoistureJson.as<float>();
    thresholdsPrefs.humidity = humidityJson.as<float>();
    thresholdsPrefs.light = lightJson.as<float>();

    PreferencesAdapter::setThresholdsPreferences(thresholdsPrefs);
}

void SystemConfigCallbackHandler::eraseThresholds()
{
    Serial.println(__FUNCTION__);
    Serial.println("Received erase command");
    PreferencesAdapter::eraseThresholdsPreferences();
}

void SystemConfigCallbackHandler::onRead(BLECharacteristic *pCharacteristic)
{
    Serial.println("BLE onRead request");
    String thresholds = "";

    String encodedString = cipher->encryptString(thresholdSerializer->getThresholdData());

    pCharacteristic->setValue(std::string(encodedString.c_str()));

    jsonBuffer.clear();
}

void SystemConfigCallbackHandler::onWrite(BLECharacteristic *pCharacteristic)
{
    Serial.println(__FUNCTION__);
    /** Json object for incoming data */
    Serial.println("On write request");
    deserializeJson(jsonBuffer, decodeData(pCharacteristic));

    JsonObject jsonIn = jsonBuffer.as<JsonObject>();
    if (!jsonIn.isNull())
    {
        JsonVariant command = jsonIn["command"];
        if (!command.isNull())
        {
            switch(translateStringToCommand(command.as<String>()))
            {
                case ThresholdsDefinition::SET_NEW_THRESHOLDS:
                {
                    Serial.println("Command SET_NEW_THRESHOLDS was called");
                    JsonVariant arguments = jsonIn["arguments"][0];
                    if(arguments.isNull())
                    {
                        Serial.println("No arumgents provided, could not connect to WiFi");
                        return;
                    }
                    setNewThresholdsSettings(arguments);
                    break;
                }
                case ThresholdsDefinition::ERASE:
                {
                    Serial.println("Command ERASE was called");
                    eraseThresholds();
                    break;
                }
                case ThresholdsDefinition::RESET:
                {
                    Serial.println("Command RESET was called");
                    esp_restart();
                    break;
                }
                case ThresholdsDefinition::UNKNOWN:
                    break;
            }
        }
        Serial.println("No command find in JSON");
    }
    else
        Serial.println("Received invalid JSON");

    jsonBuffer.clear();
}


}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse