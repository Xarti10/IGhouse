#include "DhtSensorType.hpp"
#include <mutex>
#include <memory>
#include "DHT.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

std::mutex DhtSensorType::dhtSensorGuard;

DhtSensorType::DhtSensorType(MeasurementType measType)
: Sensor(measType)
, dhtSensor(nullptr)
{
    initSensor();
}

void DhtSensorType::initSensor()
{
    pinMode(dhtPin, OUTPUT);
    dhtSensor.reset(new DHT(dhtPin, DHT21));
    dhtSensor->begin();
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse