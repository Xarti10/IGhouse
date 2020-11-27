#include "Sensor.hpp"
#include "../Utils/TypeDefinitions.hpp"
#include "../Utils/Measurement.hpp"
#include "../Utils/PinDefinitions.hpp"

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