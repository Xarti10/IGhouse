#ifndef SZKLARNIA_SYSTEMCONFIGCALLBACKHANDLER_HPP
#define SZKLARNIA_SYSTEMCONFIGCALLBACKHANDLER_HPP

#include "Arduino.h"

#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"
#include <ArduinoJson.h>
#include <Preferences.h>

#include <cstdint>
#include <memory>
#include <Utils/ThresholdSerializer.hpp>
#include "CipherAES.h"
#include "CharacteristicCallbackHandler.hpp"

namespace IGHouse
{
namespace Connection
{
namespace Drv
{
namespace Bluetooth
{

class SystemConfigCallbackHandler : public CharacteristicCallbackHandler
{
public:
    SystemConfigCallbackHandler() = delete;
    explicit SystemConfigCallbackHandler(std::shared_ptr<CipherAES> &cipher,std::shared_ptr<ThresholdSerializer> &thresholdSerializer, std::uint16_t jsonBufferSize = 256);
    virtual ~SystemConfigCallbackHandler() = default;

    void onRead(BLECharacteristic *pCharacteristic) override;
    void onWrite(BLECharacteristic *pCharacteristic) override;

private:
    DynamicJsonDocument jsonBuffer;
    std::shared_ptr<ThresholdSerializer> thresholdSerializer;

    void setNewThresholdsSettings(JsonVariant thresholds);
    void eraseThresholds();
};

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_SYSTEMCONFIGCALLBACKHANDLER_HPP
