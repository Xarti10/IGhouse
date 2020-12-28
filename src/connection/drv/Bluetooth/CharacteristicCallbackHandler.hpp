#ifndef SZKLARNIA_CHARACTERISTICCALLBACKHANDLER_HPP
#define SZKLARNIA_CHARACTERISTICCALLBACKHANDLER_HPP

#include <memory>

#include <Arduino.h>

#include "BLEUtils.h"
#include "BLEServer.h"
#include "BLEDevice.h"
#include "BLEAdvertising.h"

#include "CipherAES.h"


namespace IGHouse
{
namespace Connection
{
namespace Drv
{
namespace Bluetooth
{

class CharacteristicCallbackHandler : public BLECharacteristicCallbacks
{
public:
    CharacteristicCallbackHandler() = delete;
    CharacteristicCallbackHandler(std::shared_ptr<CipherAES> &cipher);
    virtual ~CharacteristicCallbackHandler() = default;

    String decodeData(BLECharacteristic *pCharacteristic);
protected:
    std::shared_ptr<CipherAES> cipher;
};

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_CHARACTERISTICCALLBACKHANDLER_HPP
