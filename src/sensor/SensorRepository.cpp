#include "SensorRepository.hpp"
#include "SensorFactory.hpp"

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

    sensorMap.insert(MeasurementPair (MeasurementType::LIGHT,
                                      SensorFactory::createSensorDriver(MeasurementType::LIGHT)));

    sensorMap.insert(MeasurementPair (MeasurementType::WATER_LEVEL,
                                      SensorFactory::createSensorDriver(MeasurementType::WATER_LEVEL)));

    sensorMap.insert(MeasurementPair (MeasurementType::HUMIDIDY,
                                      SensorFactory::createSensorDriver(MeasurementType::HUMIDIDY)));

    sensorMap.insert(MeasurementPair (MeasurementType::TEMPERATURE,
                                      SensorFactory::createSensorDriver(MeasurementType::TEMPERATURE)));

    sensorMap.insert(MeasurementPair (MeasurementType::SOIL_MOISTURE,
                                      SensorFactory::createSensorDriver(MeasurementType::SOIL_MOISTURE)));
}

}//namespace IGHouse