#include "LightMechanism.hpp"
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

}

void LightMechanism::runObservation()
{

}

void LightMechanism::turnOff()
{

}

void LightMechanism::turnOn()
{

}

void LightMechanism::init()
{

}

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse