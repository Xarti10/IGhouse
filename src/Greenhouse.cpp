#include "Greenhouse.hpp"
#include "sensor/SensorRepository.hpp"
#include "mechanism/MechanismRepository.hpp"
#include <memory>
#include "Arduino.h"


namespace IGHouse
{

IGHouse::Greenhouse::Greenhouse()
: sensorRepo(std::make_shared<SensorRepository>())
, mechanismRepo(nullptr/*std::make_shared<MechanismRepository>(sensorRepo)*/)
, measHandler(std::make_shared<Handlers::MeasurementHandler>(sensorRepo, 5000))
{
    delay(5000);
}

void IGHouse::Greenhouse::runMeasurements()
{
    measHandler->runMeasuremenentTask();
}

void IGHouse::Greenhouse::publishMeasurements()
{
// TODO implement publishing measurements
}

}//namespace IGHouse