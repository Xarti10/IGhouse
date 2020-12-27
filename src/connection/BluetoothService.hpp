#ifndef SZKLARNIA_BLUETOOTHHANDLER_HPP
#define SZKLARNIA_BLUETOOTHHANDLER_HPP

#include "Arduino.h"
#include <memory>
#include <connection/drv/Bluetooth/ServerCallbackHandler.hpp>
#include <connection/drv/Bluetooth/WiFiCallbackHandler.hpp>
#include <Utils/MeasurementSerializer.hpp>

#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"
#include "Cipher.h"


#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define WIFI_CHARACT_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define SENSOR_READINGS_CHARACT_UUID "a9c9a4fa-a4d6-4a66-ad3b-65cb42adaada"
#define SYSTEM_CONFIG_CHARACT_UUID "6f3cf4f8-7927-49a7-adeb-c872119bf023"

namespace IGHouse
{
namespace Connection
{

class BluetoothService
{
public:
    BluetoothService() = delete;
    BluetoothService(std::shared_ptr<MeasurementSerializer> &measSerializer, TaskHandle_t &taskHandle);
    ~BluetoothService();

private:
    std::shared_ptr<BLEAdvertising> advertising;
    std::shared_ptr<BLECharacteristic> wifiCharacteristic;
    std::shared_ptr<BLECharacteristic> sensorReadingsCharacteristic;
    std::shared_ptr<BLECharacteristic> systemConfigCharacteristic;
    std::shared_ptr<BLEService> service;
    std::shared_ptr<BLEServer> server;
    String accessPointName;
    std::shared_ptr<Cipher> cipher;
    std::shared_ptr<MeasurementSerializer> measSerializer;
    TaskHandle_t connectionTaskHandler;

    void createUniqueName();
    void init();
};

}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_BLUETOOTHHANDLER_HPP
