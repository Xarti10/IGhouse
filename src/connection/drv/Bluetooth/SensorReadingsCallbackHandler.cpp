#include "SensorReadingsCallbackHandler.hpp"

namespace IGHouse
{
namespace Connection
{
namespace Drv
{
namespace Bluetooth
{

SensorReadingsCallbackHandler::SensorReadingsCallbackHandler(std::shared_ptr<CipherAES> &cipher,
                                                             std::shared_ptr<MeasurementSerializer> &measurementSerializer)
: CharacteristicCallbackHandler(cipher)
, measSerializer(measurementSerializer)
{
}

void SensorReadingsCallbackHandler::onRead(BLECharacteristic *pCharacteristic)
{
    Serial.print("Sensor redings ");
    Serial.println(__FUNCTION__);
    String encodedString = cipher->encryptString(measSerializer->getMeasurementData());

    pCharacteristic->setValue(std::string(encodedString.c_str()));
}

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse