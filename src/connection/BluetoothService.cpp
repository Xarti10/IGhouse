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
    init();
}

void BluetoothService::createUniqueName()
{
    std::uint8_t baseMac[6];
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);

    sprintf(accessPointName, "ESP32-%02X%02X%02X%02X%02X%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3],
            baseMac[4], baseMac[5]);
}

void BluetoothService::init()
{
    BLEDevice::init(accessPointName);
    BLEDevice::setPower(ESP_PWR_LVL_P7);

    // Create BLE Server
    server.reset(BLEDevice::createServer());

    // Set server callbacks
    server->setCallbacks(serverCallbackHandler.get());

    // Create BLE Service
    service.reset(server->createService(BLEUUID(SERVICE_UUID),20));

    // Create BLE Characteristic for WiFi settings
    characteristic.reset(service->createCharacteristic(BLEUUID(CHARACTERISTIC_UUID),
                                                       BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    ));
    characteristic->setCallbacks(deviceCallbackHandler.get());

    // Start the service
    service->start();

    // Start advertising
    advertising.reset(server->getAdvertising());
    advertising->start();
}

}//namespace Connection
}//namespace IGHouse