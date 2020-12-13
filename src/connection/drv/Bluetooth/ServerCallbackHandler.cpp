#include "ServerCallbackHandler.hpp"

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

namespace IGHouse
{
namespace Connection
{
namespace Drv
{
namespace Bluetooth
{

ServerCallbackHandler::ServerCallbackHandler(std::shared_ptr <BLEAdvertising> &pAdvertising)
: pAdvertising(pAdvertising)
{

}

void ServerCallbackHandler::onConnect(BLEServer *pServer)
{
    Serial.println("BLE client connected");
}

void ServerCallbackHandler::onDisconnect(BLEServer *pServer)
{
    Serial.println("BLE client disconnected");
    pAdvertising->start();
}

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse