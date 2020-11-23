#include "SoilMoistureSensor.hpp"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{


SoilMoistureSensor::SoilMoistureSensor(MeasurementType measType)
: Sensor(measType)
{
    initSensor();
}

void SoilMoistureSensor::measure()
{
//    TODO implement
}

void SoilMoistureSensor::initSensor()
{
//    TODO implement
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse