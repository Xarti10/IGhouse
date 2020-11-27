#include "Mechanism.hpp"

namespace IGHouse
{
namespace Mechanism
{

Mechanism::Mechanism(MechanismType mechType,std::shared_ptr<Sensor::SensorInterface> sensorDrv, std::uint8_t mechPin)
: mechanismType(mechType)
, sensor(sensorDrv)
, mechanismPin(mechPin)
{
}


}//namespace Mechanism
}//namespace IGHouse