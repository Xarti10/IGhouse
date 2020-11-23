#ifndef IGHOUSE_SENSORREPOSITORY_HPP
#define IGHOUSE_SENSORREPOSITORY_HPP

#include <map>
#include <memory>

#include "../Utils/TypeDefinitions.h"
#include "SensorInterface.hpp"

namespace IGHouse
{

typedef std::map<MeasurementType, std::shared_ptr<Sensor::SensorInterface>> SensorRepositoryMap;


class SensorRepository {
public:
    SensorRepository();

    SensorRepositoryMap getSensorRepo();
    std::shared_ptr<Sensor::SensorInterface> findSensor(MeasurementType measType);
//    TODO implement all methods
private:
    SensorRepositoryMap sensorRepo;

    void createSensors();
};

}//namespace IGHouse

#endif //IGHOUSE_SENSORREPOSITORY_HPP
