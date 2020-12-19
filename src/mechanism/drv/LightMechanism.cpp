#include "LightMechanism.hpp"
#include "Arduino.h"
#include <Utils/PinDefinitions.hpp>
#include <Preferences.h>

namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

LightMechanism::LightMechanism(MechanismType mechType,
                               const std::shared_ptr<Sensor::SensorInterface> &sensorDrv,
                               uint8_t mechPin)
: Mechanism(mechType, sensorDrv, mechPin)
{
    init();
}

void LightMechanism::monitorFunction()
{
    Preferences preferences;
    preferences.begin("Thresholds", false);
    auto lightThreshold = preferences.getFloat("light", defaultLightLevelThreshold);
    preferences.end();

    if(sensor->getMeasurement()->getMeasurementValue() < lightThreshold)
    {
        turnOn();
    }
    else if (sensor->getMeasurement()->getMeasurementValue() > lightThreshold + 5)
    {
        turnOff();
    }
}

void LightMechanism::turnOff()
{
    digitalWrite(mechanismPin, LOW);
}

void LightMechanism::turnOn()
{
    digitalWrite(mechanismPin, HIGH);
}

void LightMechanism::init()
{
    pinMode(mechanismPin, OUTPUT);
    digitalWrite(mechanismPin, LOW);
}

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse