#include "Greenhouse.hpp"
#include "sensor/SensorRepository.hpp"
#include "mechanism/MechanismRepository.hpp"
#include <memory>
#include <Utils/PinDefinitions.hpp>
#include "Arduino.h"


namespace IGHouse
{

IGHouse::Greenhouse::Greenhouse()
: sensorRepo(std::make_shared<SensorRepository>())
, mechanismRepo(std::make_shared<MechanismRepository>(sensorRepo))
, measSerializer(std::make_shared<MeasurementSerializer>(sensorRepo))
, thresholdSerializer(std::make_shared<ThresholdSerializer>())
, measHandler(std::make_shared<Handlers::MeasurementHandler>(sensorRepo, measSerializer, 5000))
, mechHandler(std::make_shared<Handlers::MechanismHandler>(mechanismRepo, 5000))
, connectionHandler(std::make_shared<Handlers::ConnectionHandler>(measSerializer, thresholdSerializer))
{
    delay(500);
}

void IGHouse::Greenhouse::runMeasurements()
{
    measHandler->runMeasuremenentTask();
    mechHandler->runMechanismMonitorTask();
    connectionHandler->runConnectionMonitorTask();
}

void IGHouse::Greenhouse::publishMeasurements()
{
// TODO implement publishing measurements
}

}//namespace IGHouse