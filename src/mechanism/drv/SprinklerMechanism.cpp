#include <Utils/PinDefinitions.hpp>
#include "SprinklerMechanism.hpp"
#include "Arduino.h"

namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

SprinklerMechanism::SprinklerMechanism(MechanismType mechType,
                                       const std::shared_ptr<Sensor::SensorInterface> &sensorDrv,
                                       uint8_t mechPin)
: Mechanism(mechType, sensorDrv, mechPin)
{
    init();
}

void IGHouse::Mechanism::Drv::SprinklerMechanism::monitorFunction()
{
    if(sensor->getMeasurement()->getMeasurementValue() < humidityLevelBound)
    {
        turnOn();
    }
    else if(sensor->getMeasurement()->getMeasurementValue() > (humidityLevelBound + 5.0))
    {
        turnOff();
    }
}

void IGHouse::Mechanism::Drv::SprinklerMechanism::turnOff()
{
    digitalWrite(mechanismPin, LOW);
}

void IGHouse::Mechanism::Drv::SprinklerMechanism::turnOn()
{
    digitalWrite(mechanismPin, HIGH);
}

void IGHouse::Mechanism::Drv::SprinklerMechanism::init()
{
    pinMode(mechanismPin, OUTPUT);
    digitalWrite(mechanismPin, LOW);
}

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse