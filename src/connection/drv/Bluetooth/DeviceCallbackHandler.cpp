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

DeviceCallbackHandler::DeviceCallbackHandler(String &accessPointName,
                                             std::shared_ptr<BLECharacteristic> &characteristic,
                                             std::uint16_t jsonBufferSize)
: accessPointName(accessPointName)
, ssid("xxx")
, password("xxxxxx")
, jsonBuffer(jsonBufferSize)
, characteristics(characteristic)
, cipher(std::make_shared<Cipher>())
{
    Serial.println(__FUNCTION__);
//    auto keyFromAccessPointName = new std::uint8_t [accessPointName.length()];
//    accessPointName.getBytes(keyFromAccessPointName, accessPointName.length());

//    aes->setKey(keyFromAccessPointName, aes->keySize());
//    delete keyFromAccessPointName;
    char *keyFromAccessPointName = new char[accessPointName.length()+1];
    strcpy(keyFromAccessPointName, accessPointName.c_str());
    cipher->setKey(keyFromAccessPointName);
}

String DeviceCallbackHandler::decodeData(BLECharacteristic *pCharacteristic)
{
    Serial.println(__FUNCTION__);
    std::string value = pCharacteristic->getValue();
    if (value.length() == 0) {
        return "";
    }
    delay(50);
    Serial.print("Received over BLE: ");
    Serial.println( String((char *)&value[0]));

    String decodedValue = cipher->decryptString(String(value.c_str()));
    Serial.println(decodedValue);

    return decodedValue;
}

void DeviceCallbackHandler::fillWiFiCredentials(JsonVariant arguments)
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

void DeviceCallbackHandler::eraseWiFiCredentials()
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

void DeviceCallbackHandler::onWrite(BLECharacteristic *pCharacteristic)
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
                case Command::CONNECT_TO_WIFI:
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
                case Command::ERASE:
                {
                    Serial.println("Command ERASE was called");
                    eraseWiFiCredentials();
                    break;
                }
                case Command::RESET:
                {
                    Serial.println("Command RESET was called");
//                    WiFi.disconnect();
                    esp_restart();
                    break;
                }
                case Command::GET_SENSOR_DATA:
                {
                    Serial.println("Command GET_SENSOR_DATA was called");
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