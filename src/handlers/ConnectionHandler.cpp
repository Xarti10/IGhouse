#include "ConnectionHandler.hpp"

#include <connection/BluetoothService.hpp>
#include <connection/WiFiService.hpp>
#include <memory>
#include "FreeRTOS.h"


namespace IGHouse
{
namespace Handlers
{

ConnectionHandler::ConnectionHandler(std::shared_ptr<MeasurementSerializer> &measurementSerializer, std::uint32_t stackDepth)
: measSerializer(measurementSerializer)
, stackSize(stackDepth)
, taskHandle(nullptr)
, bluetoothService(nullptr)
, wifiService(nullptr)
, isConnected(false)
, hasCredentials(false)
, connectionStatusChanged(false)
, initialized(false)
{
}

ConnectionHandler::~ConnectionHandler()
{
    vTaskDelete(taskHandle);
}

void ConnectionHandler::connectToWiFi()
{
    if(wifiService->scanWiFi())
    {
        wifiService->connectWiFi();
    }
}

void ConnectionHandler::runConnectionMonitorTask()
{
    xTaskCreate(&runConnectionMonitor, "Connection Measurements", stackSize, this, tskIDLE_PRIORITY, &taskHandle);
    delay(500);
    bluetoothService.reset( new Connection::BluetoothService(measSerializer, taskHandle));
    wifiService.reset(new Connection::WiFiService(taskHandle));
    hasCredentials = wifiService->getNewPreferences();
    if (hasCredentials)
    {
        connectToWiFi();
    }
    initialized = true;
    delay(500);
}

void ConnectionHandler::connectionMonitor()
{
    Serial.println("ConnectionHandler task created");
    constexpr TickType_t taskDelay = pdMS_TO_TICKS(5000);
    BaseType_t notifyResult;
    std::uint32_t notificationValue;

    while(true)
    {
        notifyResult = xTaskNotifyWait(0X00, ULONG_MAX, &notificationValue, taskDelay*5);
        isConnected = WiFi.isConnected();

        if(notifyResult == pdPASS)
        {
            switch (notificationValue)
            {
                case 0x01:
                {
                    Serial.println("New wifi credentials recieved");
                    hasCredentials = wifiService->getNewPreferences();
                    Serial.println("New credensials were parsed");
//                    connectToWiFi();
//                    vTaskDelay(taskDelay);
                    break;
                }
                case 0x02:
                {
                    Serial.println("Erase configs command was send");
                    isConnected = false;
                    hasCredentials = true;
                    connectionStatusChanged = true;
                    if(WiFi.isConnected())
                        WiFi.disconnect();
//                    vTaskDelay(taskDelay);
                    break;
                }
                case 0x03:
                {
                    Serial.println("Lost connection");
                    Serial.println(WiFi.isConnected()? "WiFi connected" : "WiFi not connected");
                    isConnected = false;
                    connectionStatusChanged = true;
                    break;
                }
                case 0x04:
                {
                    Serial.println("Device is connected");
                    Serial.println(WiFi.isConnected()? "WiFi connected" : "WiFi not connected");
                    isConnected = true;
                    break;
                }
                default:
                {
                    Serial.print("Unknown notification recived, Value: ");
                    Serial.println(notificationValue);
                    break;
                }
            }
        }
        else if (!isConnected && hasCredentials && initialized && connectionStatusChanged)
        {
            Serial.println("Wifi is not connected, trying to reconect...");
            connectToWiFi();
            vTaskDelay(taskDelay);
            connectionStatusChanged = false;
        }
        vTaskDelay(taskDelay);
    }
}

void ConnectionHandler::runConnectionMonitor(void *params)
{
    static_cast <ConnectionHandler *>(params)->connectionMonitor();
}

}//namespace Handlers
}//namespace IGHouse