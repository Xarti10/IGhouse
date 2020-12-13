#ifndef SZKLARNIA_SERVERCALLBACKHANDLER_HPP
#define SZKLARNIA_SERVERCALLBACKHANDLER_HPP

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

class ServerCallbackHandler : public BLEServerCallbacks
{
public:
    ServerCallbackHandler() = delete;

    ServerCallbackHandler(std::shared_ptr <BLEAdvertising> &pAdvertising);

    virtual ~ServerCallbackHandler() = default;

    void onConnect(BLEServer *pServer) override;

    void onDisconnect(BLEServer *pServer) override;

private:
    std::shared_ptr <BLEAdvertising> pAdvertising;
};

}//namesapce Bluetooth
}//namespace Drv
}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_SERVERCALLBACKHANDLER_HPP
