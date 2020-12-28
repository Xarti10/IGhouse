#ifndef SZKLARNIA_CONNECTIONHANDLER_HPP
#define SZKLARNIA_CONNECTIONHANDLER_HPP

#include <memory>
#include "Arduino.h"

#include <connection/BluetoothService.hpp>
#include <connection/WiFiService.hpp>
#include <Utils/ThresholdSerializer.hpp>
#include <connection/ServerClientService.hpp>

namespace IGHouse
{
namespace Handlers
{

class ConnectionHandler
{
public:
    ConnectionHandler()= delete;
    explicit ConnectionHandler(std::shared_ptr<MeasurementSerializer> &measurementSerializer,
                               std::shared_ptr<ThresholdSerializer> &thresholdSerializer,
                               std::uint32_t stackDepth = configMINIMAL_STACK_SIZE);
    ~ConnectionHandler();

    void runConnectionMonitorTask();
    [[noreturn]] void connectionMonitor();

private:
    std::shared_ptr<MeasurementSerializer> measSerializer;
    std::shared_ptr<ThresholdSerializer> thresholdSerializer;
    std::uint32_t stackSize;
    TaskHandle_t taskHandle;
    std::shared_ptr<Connection::BluetoothService> bluetoothService;
    std::shared_ptr<Connection::WiFiService> wifiService;
    bool isConnected;
    bool hasCredentials;
    bool connectionStatusChanged;
    bool initialized;
    String accessPointName;
    std::shared_ptr<Connection::ServerClientService> serverClientService;

    void createUniqueName();
    static void runConnectionMonitor(void *params);
    void connectToWiFi();
};

}//namespace Handlers
}//namespace IGHouse

#endif //SZKLARNIA_CONNECTIONHANDLER_HPP
