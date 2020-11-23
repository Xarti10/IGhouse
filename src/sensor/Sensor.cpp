#include "Sensor.hpp"
#include "../Utils/TypeDefinitions.h"
#include "../Utils/Measurement.h"

#include <memory>

namespace IGHouse
{
namespace Sensor
{

Sensor::Sensor(MeasurementType measType)
: sensorMeasType(measType), sensorMeas(std::make_shared<Measurement>(measType))
{
}

std::shared_ptr<Measurement> Sensor::getMeasurement()
{
    return sensorMeas;
}

MeasurementType Sensor::getMeasurementType()
{
    return sensorMeasType;
}

}//namespace Sensor
}//namespace IGHouse