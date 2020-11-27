#include "SprinklerMechanism.hpp"

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

void IGHouse::Mechanism::Drv::SprinklerMechanism::runObservation()
{

}

void IGHouse::Mechanism::Drv::SprinklerMechanism::turnOff()
{

}

void IGHouse::Mechanism::Drv::SprinklerMechanism::turnOn()
{

}

void IGHouse::Mechanism::Drv::SprinklerMechanism::init()
{

}

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse