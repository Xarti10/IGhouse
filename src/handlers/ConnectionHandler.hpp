#ifndef SZKLARNIA_CONNECTIONHANDLER_HPP
#define SZKLARNIA_CONNECTIONHANDLER_HPP

#include <memory>
#include "Arduino.h"

#include <connection/BluetoothService.hpp>
#include <connection/WiFiService.hpp>

namespace IGHouse
{
namespace Handlers
{

class ConnectionHandler
{
public:
    ConnectionHandler()= delete;
    explicit ConnectionHandler(std::shared_ptr<MeasurementSerializer> &measurementSerializer);
    ~ConnectionHandler() = default;

private:
    std::shared_ptr<MeasurementSerializer> measSerializer;

    std::shared_ptr<Connection::BluetoothService> bluetoothService;
    std::shared_ptr<Connection::WiFiService> wifiService;
};

}//namespace Handlers
}//namespace IGHouse

#endif //SZKLARNIA_CONNECTIONHANDLER_HPP
