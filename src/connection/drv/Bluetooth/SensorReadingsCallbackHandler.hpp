#ifndef SZKLARNIA_SENSORREADINGSCALLBACKHANDLER_HPP
#define SZKLARNIA_SENSORREADINGSCALLBACKHANDLER_HPP

#include "Arduino.h"

#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"
#include <ArduinoJson.h>

#include <cstdint>
#include <memory>
#include <Utils/MeasurementSerializer.hpp>
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

class SensorReadingsCallbackHandler : public CharacteristicCallbackHandler
{
public:
    SensorReadingsCallbackHandler() = delete;
    explicit SensorReadingsCallbackHandler(std::shared_ptr<Cipher> &cipher,
                                           std::shared_ptr<MeasurementSerializer> &measurementSerializer);
    virtual ~SensorReadingsCallbackHandler() = default;

    void onRead(BLECharacteristic *pCharacteristic) override;

private:
    std::shared_ptr<MeasurementSerializer> measSerializer;
};

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_SENSORREADINGSCALLBACKHANDLER_HPP
