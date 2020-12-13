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

namespace IGHouse
{
namespace Connection
{

class BluetoothService
{
public:
    BluetoothService();

private:
    std::shared_ptr<BLEAdvertising> advertising;
    std::shared_ptr<BLECharacteristic> characteristic;
    char *accessPointName;
    static constexpr char *SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
    static constexpr char *CHARACTERISTIC_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b";
    std::shared_ptr<Drv::Bluetooth::DeviceCallbackHandler> deviceCallbackHandler;
    std::shared_ptr<Drv::Bluetooth::ServerCallbackHandler> serverCallbackHandler;

    void createUniqueName();
};

}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_BLUETOOTHHANDLER_HPP
