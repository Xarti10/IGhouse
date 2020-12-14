#include "SensorRepository.hpp"
#include "SensorFactory.hpp"
#include "Arduino.h"
#include <memory>

namespace IGHouse
{

SensorRepository::SensorRepository()
{
    createSensors();
}

SensorRepository::SensorRepositoryMap SensorRepository::getSensorMap()
{
    return sensorMap;
}

std::shared_ptr<Sensor::SensorInterface> SensorRepository::findSensor(MeasurementType measType)
{
    auto mechanismFind = sensorMap.find(measType);
    if (mechanismFind != sensorMap.end())
        return mechanismFind->second;
    else
        return nullptr;
}

void SensorRepository::createSensors()
{
    using namespace Sensor;
    typedef std::pair<MeasurementType, std::shared_ptr<SensorInterface>> MeasurementPair;

    for (const auto &measurementTypeIt : measurementList)
    {
        sensorMap.insert(MeasurementPair(measurementTypeIt,
                                         SensorFactory::createSensorDriver(measurementTypeIt)));
    }
}

}//namespace IGHouse