#include "IrrigationMechanism.hpp"
#include "Arduino.h"

#include <Utils/PinDefinitions.hpp>

namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

IrrigationMechanism::IrrigationMechanism(MechanismType mechType,
                                         const std::shared_ptr<Sensor::SensorInterface> &sensorDrv,
                                         uint8_t mechPin)
: Mechanism(mechType, sensorDrv, mechPin)
{
    init();
}

void IrrigationMechanism::monitorFunction()
{
    if(sensor->getMeasurement()->getMeasurementValue() < soilMoistureLevelBound)
    {
        turnOn();
    }
    else if(sensor->getMeasurement()->getMeasurementValue() > soilMoistureLevelBound + 5.0)
    {
        turnOff();
    }
}

void IrrigationMechanism::turnOff()
{
    digitalWrite(mechanismPin, LOW);
}

void IrrigationMechanism::turnOn()
{
    digitalWrite(mechanismPin, HIGH);
}

void IrrigationMechanism::init()
{
    pinMode(mechanismPin, OUTPUT);
    digitalWrite(mechanismPin, LOW);
}
}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse