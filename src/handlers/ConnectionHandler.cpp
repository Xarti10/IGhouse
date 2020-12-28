#include "ConnectionHandler.hpp"

#include <connection/BluetoothService.hpp>
#include <connection/WiFiService.hpp>
#include <memory>
#include <sstream>
#include <iomanip>
#include "FreeRTOS.h"


namespace IGHouse
{
namespace Handlers
{

ConnectionHandler::ConnectionHandler(std::shared_ptr<MeasurementSerializer> &measurementSerializer,
                                     std::shared_ptr<ThresholdSerializer> &thresholdSerializer,
                                     std::uint32_t stackDepth)
: measSerializer(measurementSerializer)
, thresholdSerializer(thresholdSerializer)
, stackSize(stackDepth)
, taskHandle(nullptr)
, bluetoothService(nullptr)
, wifiService(nullptr)
, isConnected(false)
, hasCredentials(false)
, connectionStatusChanged(false)
, initialized(false)
, accessPointName("")
, serverClientService(nullptr)
{
    createUniqueName();
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

void ConnectionHandler::createUniqueName()
{
    std::uint8_t baseMac[6];
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);

    std::ostringstream stringBuffer;
    stringBuffer << "IGHouse-" << std::hex << std::setw(2) << (unsigned int) baseMac[0] << "-"
                 << std::hex << std::setw(2) << (unsigned int) baseMac[1] << "-"
                 << std::hex << std::setw(2) << (unsigned int) baseMac[2] << "-"
                 << std::hex << std::setw(2) << (unsigned int) baseMac[3] << "-"
                 << std::hex << std::setw(2) << (unsigned int) baseMac[4] << "-"
                 << std::hex << std::setw(2) << (unsigned int) baseMac[5];

    accessPointName = stringBuffer.str().c_str();
    Serial.println(accessPointName);
}

void ConnectionHandler::runConnectionMonitorTask()
{
    xTaskCreate(&runConnectionMonitor, "Connection Measurements", stackSize, this, tskIDLE_PRIORITY, &taskHandle);
    delay(500);
    bluetoothService.reset( new Connection::BluetoothService(measSerializer, thresholdSerializer, taskHandle, accessPointName));
    wifiService.reset(new Connection::WiFiService(taskHandle));
    serverClientService.reset(new Connection::ServerClientService(measSerializer, thresholdSerializer, accessPointName));
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
        serverClientService->runLoop();
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