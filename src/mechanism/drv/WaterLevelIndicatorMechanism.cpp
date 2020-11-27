#include "WaterLevelIndicatorMechanism.hpp"

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

void WaterLevelIndicatorMechanism::runObservation()
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
//todo implement
}

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse
