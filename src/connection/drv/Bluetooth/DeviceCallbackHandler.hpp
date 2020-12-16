#ifndef SZKLARNIA_DEVICECALLBACKHANDLER_HPP
#define SZKLARNIA_DEVICECALLBACKHANDLER_HPP

#include "Arduino.h"

#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"
#include <ArduinoJson.h>
#include <Preferences.h>
#include <nvs.h>
#include <nvs_flash.h>

#include <cstdint>
#include <memory>
#include "Cipher.h"

namespace IGHouse
{
namespace Connection
{
namespace Drv
{
namespace Bluetooth
{

class DeviceCallbackHandler : public BLECharacteristicCallbacks
{
public:
    DeviceCallbackHandler() = delete;
    DeviceCallbackHandler(String &accessPointName,
                          std::shared_ptr<BLECharacteristic> &characteristic,
                          std::uint16_t jsonBufferSize = 256);
    virtual ~DeviceCallbackHandler() = default;

    void onWrite(BLECharacteristic *pCharacteristic) override;
    void onRead(BLECharacteristic *pCharacteristic) override;

private:
    String accessPointName;
    String ssid;
    String password;
    DynamicJsonDocument jsonBuffer;
    std::shared_ptr<BLECharacteristic> characteristics;
    std::shared_ptr<Cipher> cipher ;

    String decodeData(BLECharacteristic *pCharacteristic);
    void fillWiFiCredentials(JsonVariant arguments);
    void eraseWiFiCredentials();
};

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_DEVICECALLBACKHANDLER_HPP
