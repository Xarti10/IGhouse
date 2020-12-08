#include "DhtSensorType.hpp"
#include <mutex>
#include <memory>
#include "DHT.h"
#define DHTTYPE DHT21

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

std::mutex DhtSensorType::dhtSensorGuard;
bool DhtSensorType::sensorInited = false;
std::shared_ptr<DHT> DhtSensorType::dhtSensor = nullptr;

DhtSensorType::DhtSensorType(MeasurementType measType)
: Sensor(measType)
{
    initSensor();
}

void DhtSensorType::initSensor()
{
    if(!sensorInited)
    {
        Serial.println(__FUNCTION__);
        dhtSensor.reset(new DHT(dhtPin, DHTTYPE));
        dhtSensor->begin();
        sensorInited = true;
    }
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse