#include "BluetoothService.hpp"

#include <Preferences.h>
#include <nvs.h>
#include <sstream>
#include <iomanip>
#include <connection/drv/Bluetooth/SensorReadingsCallbackHandler.hpp>
#include <connection/drv/Bluetooth/SystemConfigCallbackHandler.hpp>
#include "CipherAES.h"


namespace IGHouse
{
namespace Connection
{

BluetoothService::BluetoothService(std::shared_ptr<MeasurementSerializer> &measSerializer,
                                   std::shared_ptr<ThresholdSerializer> &thresholdSerializer,
                                   TaskHandle_t &taskHandle,
                                   String &apName)
: advertising(nullptr)
, wifiCharacteristic(nullptr)
, sensorReadingsCharacteristic(nullptr)
, systemConfigCharacteristic(nullptr)
, service(nullptr)
, server(nullptr)
, accessPointName(apName)
, cipher(std::make_shared<CipherAES>())
, measSerializer(measSerializer)
, thresholdSerializer(thresholdSerializer)
, connectionTaskHandler(taskHandle)
{
    char *keyFromAccessPointName = new char[accessPointName.length()];
    strcpy(keyFromAccessPointName, accessPointName.c_str());
    cipher->setKey(keyFromAccessPointName);

    init();
}

BluetoothService::~BluetoothService()
{
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

    systemConfigCharacteristic->setCallbacks(new Drv::Bluetooth::SystemConfigCallbackHandler(cipher, thresholdSerializer));

    // Start the service
    service->start();

    // Start advertising
    advertising.reset(server->getAdvertising());

    advertising->start();
}

}//namespace Connection
}//namespace IGHouse