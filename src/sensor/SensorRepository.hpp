#ifndef IGHOUSE_SENSORREPOSITORY_HPP
#define IGHOUSE_SENSORREPOSITORY_HPP

#include <map>
#include <memory>

#include "../Utils/TypeDefinitions.hpp"
#include "SensorInterface.hpp"

namespace IGHouse
{

class SensorRepository
{
public:
    SensorRepository();

    typedef std::map<MeasurementType, std::shared_ptr<Sensor::SensorInterface>> SensorRepositoryMap;
    SensorRepositoryMap getSensorMap();
    std::shared_ptr<Sensor::SensorInterface> findSensor(MeasurementType measType);
private:
    SensorRepositoryMap sensorMap;

    void createSensors();
};

}//namespace IGHouse

#endif //IGHOUSE_SENSORREPOSITORY_HPP
