#include "BluetoothService.hpp"

#include <Preferences.h>
#include <nvs.h>
#include <sstream>
#include <iomanip>


namespace IGHouse
{
namespace Connection
{

BluetoothService::BluetoothService()
: advertising(nullptr)
, characteristic(nullptr)
, service(nullptr)
, server(nullptr)
, accessPointName("")
, deviceCallbackHandler(nullptr)
, serverCallbackHandler(nullptr)
{
    createUniqueName();
    serverCallbackHandler.reset(new Drv::Bluetooth::ServerCallbackHandler(advertising));
    deviceCallbackHandler.reset(new Drv::Bluetooth::DeviceCallbackHandler(accessPointName, characteristic));
    init();
}

BluetoothService::~BluetoothService()
{
}

void BluetoothService::createUniqueName()
{
    std::uint8_t baseMac[6];
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);

    std::ostringstream stringBuffer;
    stringBuffer << "ESP32-" << std::hex << std::setw(2) << (unsigned int) baseMac[0] << "-"
                             << std::hex << std::setw(2) << (unsigned int) baseMac[1] << "-"
                             << std::hex << std::setw(2) << (unsigned int) baseMac[2] << "-"
                             << std::hex << std::setw(2) << (unsigned int) baseMac[3] << "-"
                             << std::hex << std::setw(2) << (unsigned int) baseMac[4] << "-"
                             << std::hex << std::setw(2) << (unsigned int) baseMac[5];

    accessPointName = stringBuffer.str().c_str();
    Serial.println(accessPointName);
}

void BluetoothService::init()
{
    BLEDevice::init(accessPointName.c_str());
//    BLEDevice::setPower(ESP_PWR_LVL_P7);

    // Create BLE Server
    server.reset(BLEDevice::createServer());
    delay(50);

    // Create BLE Service
    service.reset(server->createService(BLEUUID(SERVICE_UUID),20));
    delay(50);

    // Set server callbacks
    server->setCallbacks(serverCallbackHandler.get());
    delay(50);

    // Create BLE Characteristic for WiFi settings
    characteristic.reset(service->createCharacteristic(BLEUUID(CHARACTERISTIC_UUID),
                                                       BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    ));
    delay(50);

    characteristic->setCallbacks(deviceCallbackHandler.get());
    delay(50);

    // Start the service
    service->start();
    delay(50);

    // Start advertising
    advertising.reset(server->getAdvertising());
    delay(50);

    advertising->start();
}

}//namespace Connection
}//namespace IGHouse