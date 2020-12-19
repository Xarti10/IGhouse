#include "ConnectionHandler.hpp"

#include <connection/BluetoothService.hpp>
#include <connection/WiFiService.hpp>
#include <memory>

namespace IGHouse
{
namespace Handlers
{

ConnectionHandler::ConnectionHandler(std::shared_ptr<MeasurementSerializer> &measurementSerializer)
        : measSerializer(measurementSerializer)
        , bluetoothService(std::make_shared<Connection::BluetoothService>(measurementSerializer))
        , wifiService(std::make_shared<Connection::WiFiService>())
{
    wifiService->getNewPreferences();

    if(wifiService->scanWiFi())
        wifiService->connectWiFi();
}

}//namespace Handlers
}//namespace IGHouse