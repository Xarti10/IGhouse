#include "SensorRepository.hpp"
#include <memory>

namespace IGHouse
{

SensorRepository::SensorRepository()
{
// TODO implement constructor
}

SensorRepositoryMap SensorRepository::getSensorRepo()
{
    return sensorRepo;
}

std::shared_ptr<Sensor::SensorInterface> SensorRepository::findSensor(MeasurementType measType)
{
// TODO implement search
    return nullptr;
}

void SensorRepository::createSensors()
{
// TODO implement sensor factory
}

}//namespace IGHouse