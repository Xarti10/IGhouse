#include "ServerClientService.hpp"
#include <memory>

namespace IGHouse
{
namespace Connection
{

char ServerClientService::host[] = "https://ighouse-server.herokuapp.com/"; // Socket.IO Server Address
int ServerClientService::port = 3000; // Socket.IO Port Address
char ServerClientService::path[] = "/socket.io/?transport=websocket"; // Socket.IO Base Path

String ServerClientService::accessPointName = "";
std::shared_ptr<MeasurementSerializer> ServerClientService::measSerializer;
std::shared_ptr<ThresholdSerializer> ServerClientService::thresholdSerializer;
std::shared_ptr<SocketIoClient> ServerClientService::webSocket;
std::shared_ptr<WiFiClient> ServerClientService::client = std::make_shared<WiFiClient>();
bool ServerClientService::isConnected = false;

ServerClientService::ServerClientService(std::shared_ptr<MeasurementSerializer> &measurementSerializer,
                                         std::shared_ptr<ThresholdSerializer> &thresholdSerial,
                                         String &apName)
{
    accessPointName = apName;
    measSerializer = measurementSerializer;
    thresholdSerializer = thresholdSerial;
    webSocket = std::make_shared<SocketIoClient>();

    webSocket->on("connect", connectedToServer);
    webSocket->on("disconnect", disconnectedFromServer);
    webSocket->on("get_sensor_data_update", sendSensorData);
    webSocket->on("get_threshold_data_update", sendThresholdStatuses);
    webSocket->on("update_thresholds", updateThresholdStatuses);

    webSocket->begin(host, port, path);
}

void ServerClientService::connectedToServer(const char *payload, size_t length)
{
//    webSocket->emit("sensor_data", );
    Serial.println("Device connected to socket.IO server");
    isConnected = true;
}

void ServerClientService::disconnectedFromServer(const char *payload, size_t length)
{
//    webSocket->emit("sensor_data", )
    Serial.println("Device disconnected to socket.IO server");
    isConnected = false;
}

void ServerClientService::sendSensorData(const char *payload, size_t length)
{
    if(!isConnected)
    {
        Serial.println("Failed to send sensor data to server - no connection");
        return;
    }

    String serializedString = measSerializer->getGeneratedJsonSerializedSensorDataWithApNameString(accessPointName);

    Serial.println(String("Sensor data send to server: " + serializedString));
    webSocket->emit("sensor_data", serializedString.c_str());
}

void ServerClientService::sendThresholdStatuses(const char *payload, size_t length)
{
    if(!isConnected)
    {
        Serial.println("Failed to send sensor data to server - no connection");
        return;
    }
    String serializedString = thresholdSerializer->getGeneratedJsonSerializedThresholdDataWithApNameString(accessPointName);

    Serial.println(String("Sensor data send to server: " + serializedString));
    webSocket->emit("sensor_data", serializedString.c_str());
}

void ServerClientService::updateThresholdStatuses(const char * payload, size_t length)
{
    DynamicJsonDocument jsonBuffer(192);
    deserializeJson(jsonBuffer, payload);
    auto apName = jsonBuffer["DeviceName"].as<String>();

    if(apName.equals(accessPointName))
    {
        thresholdSerializer->deserializeDataAndUpdatePreferences(String(payload));
    }
}

void ServerClientService::runLoop()
{
    webSocket->loop();
}


}//namespace Connection
}//namespace IGHouse