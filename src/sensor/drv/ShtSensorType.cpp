#include "ShtSensorType.hpp"
#include <mutex>
#include <memory>
#include "Arduino.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

std::mutex ShtSensorType::shtSensorGuard;
bool ShtSensorType::sensorInited = false;
std::shared_ptr<SHTSensor> ShtSensorType::shtSensor = nullptr;

ShtSensorType::ShtSensorType(MeasurementType measType)
: Sensor(measType)
{
    initSensor();
}

void ShtSensorType::initSensor()
{
    if(!sensorInited)
    {
        Serial.println(__FUNCTION__);
        shtSensor.reset(new SHTSensor());
        shtSensor->init();
        shtSensor->setAccuracy(SHTSensor::SHT_ACCURACY_HIGH);

        sensorInited = true;
    }
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse