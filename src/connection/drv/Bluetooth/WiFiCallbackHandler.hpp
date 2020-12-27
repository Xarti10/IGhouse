#ifndef SZKLARNIA_WIFICALLBACKHANDLER_HPP
#define SZKLARNIA_WIFICALLBACKHANDLER_HPP

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
#include "CharacteristicCallbackHandler.hpp"

namespace IGHouse
{
namespace Connection
{
namespace Drv
{
namespace Bluetooth
{

class WiFiCallbackHandler : public CharacteristicCallbackHandler
{
public:
    WiFiCallbackHandler() = delete;
    WiFiCallbackHandler(std::shared_ptr<Cipher> &cipher,
                        TaskHandle_t &taskHandle,
                        std::uint16_t jsonBufferSize = 256);
    virtual ~WiFiCallbackHandler() = default;

    void onWrite(BLECharacteristic *pCharacteristic) override;
    void onRead(BLECharacteristic *pCharacteristic) override;

private:
    TaskHandle_t connectionTaskHandler;
    DynamicJsonDocument jsonBuffer;

    void fillWiFiCredentials(JsonVariant arguments);
    void eraseWiFiCredentials();
};

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_WIFICALLBACKHANDLER_HPP
