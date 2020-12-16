#include "ServerCallbackHandler.hpp"

#include "Arduino.h"

#include "BLEServer.h"
#include "BLEAdvertising.h"

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
    pServer->getAdvertising()->start();
}

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse