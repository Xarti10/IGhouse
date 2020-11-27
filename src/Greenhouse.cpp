#include "Greenhouse.hpp"
#include "sensor/SensorRepository.hpp"
#include "mechanism/MechanismRepository.hpp"
#include <memory>


namespace IGHouse
{

IGHouse::Greenhouse::Greenhouse()
: sensorRepo(std::make_shared<SensorRepository>())
, mechanismRepo(std::make_shared<MechanismRepository>(sensorRepo))
{
// TODO implement constructor
}

void IGHouse::Greenhouse::runMeasurements()
{
// TODO implement runnig measurements
}

void IGHouse::Greenhouse::publishMeasurements()
{
// TODO implement publishing measurements
}

}//namespace IGHouse