#include "WaterLevelIndicatorMechanism.hpp"
#include "Arduino.h"

namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

WaterLevelIndicatorMechanism::WaterLevelIndicatorMechanism(MechanismType mechType,
                                                           const std::shared_ptr<Sensor::SensorInterface> &sensorDrv,
                                                           uint8_t mechPin)
        : Mechanism(mechType, sensorDrv, mechPin)
{
    init();
}

void WaterLevelIndicatorMechanism::monitorFunction()
{
//todo implement
}

void WaterLevelIndicatorMechanism::turnOff()
{
//todo implement
}

void WaterLevelIndicatorMechanism::turnOn()
{
//todo implement
}

void WaterLevelIndicatorMechanism::init()
{
    pinMode(mechanismPin, OUTPUT);
    digitalWrite(mechanismPin, LOW);
}

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse
