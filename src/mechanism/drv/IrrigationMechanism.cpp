#include "IrrigationMechanism.hpp"

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

}

void IrrigationMechanism::runObservation()
{

}

void IrrigationMechanism::turnOff()
{

}

void IrrigationMechanism::turnOn()
{

}

void IrrigationMechanism::init()
{

}
}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse