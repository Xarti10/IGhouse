#ifndef SZKLARNIA_SERVERCLIENTSERVICE_HPP
#define SZKLARNIA_SERVERCLIENTSERVICE_HPP

#include <memory>
#include <SocketIoClient.h>
#include <sensor/SensorRepository.hpp>
#include <Utils/MeasurementSerializer.hpp>
#include <Utils/ThresholdSerializer.hpp>

namespace IGHouse
{
namespace Connection
{

class ServerClientService
{
public:
    ServerClientService() = delete;
    explicit ServerClientService(std::shared_ptr<MeasurementSerializer> &measurementSerializer,
                                 std::shared_ptr<ThresholdSerializer> &thresholdSerial,
                                 String &apName);

    void runLoop();

private:
    static String accessPointName;
    static std::shared_ptr<MeasurementSerializer> measSerializer;
    static std::shared_ptr<ThresholdSerializer> thresholdSerializer;
    static std::shared_ptr<SocketIoClient> webSocket;

    static bool isConnected;

    static char host[];
    static int port;
    static char path[];


    static void connectedToServer(const char * payload, size_t length);
    static void disconnectedFromServer(const char *payload, size_t length);
    static void updateThresholdStatuses(const char * payload, size_t length);
    static void sendSensorData(const char *payload, size_t length);
    static void sendThresholdStatuses(const char *payload, size_t length);




};

}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_SERVERCLIENTSERVICE_HPP
