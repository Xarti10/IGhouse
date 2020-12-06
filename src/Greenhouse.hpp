#ifndef IGHOUSE_GREENHOUSE_HPP
#define IGHOUSE_GREENHOUSE_HPP

#include "sensor/SensorRepository.hpp"
#include "mechanism/MechanismRepository.hpp"
#include "handlers/MeasurementHandler.hpp"

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
    std::shared_ptr<Handlers::MeasurementHandler> measHandler;
};

}//namespace IGHouse

#endif //IGHOUSE_GREENHOUSE_HPP
