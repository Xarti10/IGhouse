#ifndef IGHOUSE_GREENHOUSE_HPP
#define IGHOUSE_GREENHOUSE_HPP

#include "sensor/SensorRepository.hpp"
#include "mechanism/MechanismRepository.hpp"

namespace IGHouse {

class Greenhouse {
public:
    Greenhouse();

    void runMeasurements();

    void publishMeasurements();

private:
//TODO: add all pointers from uml
    std::shared_ptr<SensorRepository> sensorRepo;
    std::shared_ptr<MechanismRepository> mechanismRepo;
};

}//namespace IGHouse

#endif //IGHOUSE_GREENHOUSE_HPP
