#ifndef SZKLARNIA_CONNECTIONHANDLER_HPP
#define SZKLARNIA_CONNECTIONHANDLER_HPP

#include <memory>
#include "Arduino.h"

#include <connection/BluetoothService.hpp>

namespace IGHouse
{
namespace Handlers
{

class ConnectionHandler
{
public:
    ConnectionHandler();

private:
    std::shared_ptr<Connection::BluetoothService> bluetoothService;
};

}//namespace Handlers
}//namespace IGHouse

#endif //SZKLARNIA_CONNECTIONHANDLER_HPP
