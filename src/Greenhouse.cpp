#include "Greenhouse.hpp"
#include "sensor/SensorRepository.hpp"
#include "mechanism/MechanismRepository.hpp"
#include <memory>
#include "Arduino.h"


namespace IGHouse
{

IGHouse::Greenhouse::Greenhouse()
: sensorRepo(std::make_shared<SensorRepository>())
, mechanismRepo(std::make_shared<MechanismRepository>(sensorRepo))
, measHandler(std::make_shared<Handlers::MeasurementHandler>(sensorRepo, 5000))
, mechHandler(std::make_shared<Handlers::MechanismHandler>(mechanismRepo, 5000))
, connectionHandler(std::make_shared<Handlers::ConnectionHandler>())
{
    delay(500);
}

void IGHouse::Greenhouse::runMeasurements()
{
    measHandler->runMeasuremenentTask();
    mechHandler->runMechanismMonitorTask();
}

void IGHouse::Greenhouse::publishMeasurements()
{
// TODO implement publishing measurements
}

}//namespace IGHouse