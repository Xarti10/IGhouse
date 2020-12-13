#include "BluetoothService.hpp"

#include <ArduinoJson.h>
#include <Preferences.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <memory>
#include <string>


namespace IGHouse
{
namespace Connection
{

BluetoothService::BluetoothService()
: accessPointName()
, deviceCallbackHandler(nullptr)
, serverCallbackHandler(nullptr)
{
    createUniqueName();
    serverCallbackHandler.reset(new Drv::Bluetooth::ServerCallbackHandler(advertising));
    deviceCallbackHandler.reset(new Drv::Bluetooth::DeviceCallbackHandler(accessPointName, characteristic));
}

void BluetoothService::createUniqueName()
{
    std::uint8_t baseMac[6];
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);

    sprintf(accessPointName, "ESP32-%02X%02X%02X%02X%02X%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3],
            baseMac[4], baseMac[5]);
}

}//namespace Connection
}//namespace IGHouse