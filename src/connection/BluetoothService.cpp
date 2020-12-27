#include "BluetoothService.hpp"

#include <Preferences.h>
#include <nvs.h>
#include <sstream>
#include <iomanip>
#include <connection/drv/Bluetooth/SensorReadingsCallbackHandler.hpp>
#include <connection/drv/Bluetooth/SystemConfigCallbackHandler.hpp>
#include "Cipher.h"


namespace IGHouse
{
namespace Connection
{

BluetoothService::BluetoothService(std::shared_ptr<MeasurementSerializer> &measSerializer, TaskHandle_t &taskHandle)
: advertising(nullptr)
, wifiCharacteristic(nullptr)
, sensorReadingsCharacteristic(nullptr)
, systemConfigCharacteristic(nullptr)
, service(nullptr)
, server(nullptr)
, accessPointName("")
, cipher(std::make_shared<Cipher>())
, measSerializer(measSerializer)
, connectionTaskHandler(taskHandle)
{
    createUniqueName();

    char *keyFromAccessPointName = new char[accessPointName.length()];
    strcpy(keyFromAccessPointName, accessPointName.c_str());
    cipher->setKey(keyFromAccessPointName);

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
    stringBuffer << "IGHouse-" << std::hex << std::setw(2) << (unsigned int) baseMac[0] << "-"
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

    // Create BLE Service
    service.reset(server->createService(BLEUUID(SERVICE_UUID),20));

    // Set server callbacks
    server->setCallbacks(new Drv::Bluetooth::ServerCallbackHandler(advertising));

    // Create BLE Characteristic for WiFi settings
    wifiCharacteristic.reset(service->createCharacteristic(BLEUUID(WIFI_CHARACT_UUID),
                                                           BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
    ));

    wifiCharacteristic->setCallbacks(new Drv::Bluetooth::WiFiCallbackHandler(cipher, connectionTaskHandler));

    sensorReadingsCharacteristic.reset(service->createCharacteristic(BLEUUID(SENSOR_READINGS_CHARACT_UUID),
                                                                         BLECharacteristic::PROPERTY_READ));

    sensorReadingsCharacteristic->setCallbacks(new Drv::Bluetooth::SensorReadingsCallbackHandler(cipher,measSerializer));

    systemConfigCharacteristic.reset(service->createCharacteristic(BLEUUID(SYSTEM_CONFIG_CHARACT_UUID),
                                                                   BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE));

    systemConfigCharacteristic->setCallbacks(new Drv::Bluetooth::SystemConfigCallbackHandler(cipher));

    // Start the service
    service->start();

    // Start advertising
    advertising.reset(server->getAdvertising());

    advertising->start();
}

}//namespace Connection
}//namespace IGHouse