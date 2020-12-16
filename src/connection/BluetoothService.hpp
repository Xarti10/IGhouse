#ifndef SZKLARNIA_BLUETOOTHHANDLER_HPP
#define SZKLARNIA_BLUETOOTHHANDLER_HPP

#include "Arduino.h"
#include <memory>
#include <connection/drv/Bluetooth/ServerCallbackHandler.hpp>
#include <connection/drv/Bluetooth/DeviceCallbackHandler.hpp>

#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

namespace IGHouse
{
namespace Connection
{

class BluetoothService
{
public:
    BluetoothService();
    ~BluetoothService();

private:
    std::shared_ptr<BLEAdvertising> advertising;
    std::shared_ptr<BLECharacteristic> characteristic;
    std::shared_ptr<BLEService> service;
    std::shared_ptr<BLEServer> server;
    String accessPointName;

    std::shared_ptr<Drv::Bluetooth::DeviceCallbackHandler> deviceCallbackHandler;
    std::shared_ptr<Drv::Bluetooth::ServerCallbackHandler> serverCallbackHandler;

    void createUniqueName();
    void init();
};

}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_BLUETOOTHHANDLER_HPP
