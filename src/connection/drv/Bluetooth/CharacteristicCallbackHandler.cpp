#include "CharacteristicCallbackHandler.hpp"

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

CharacteristicCallbackHandler::CharacteristicCallbackHandler(std::shared_ptr<CipherAES> &cipher)
        : cipher(cipher)
{
}

String CharacteristicCallbackHandler::decodeData(BLECharacteristic *pCharacteristic)
{
    Serial.println(__FUNCTION__);
    std::string value = pCharacteristic->getValue();
    if (value.length() == 0) {
        return "";
    }

    Serial.print("Received over BLE: ");
    Serial.println( String((char *)&value[0]));

    String decodedValue = cipher->decryptString(String(value.c_str()));
    Serial.println(decodedValue);

    return decodedValue;
}

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse