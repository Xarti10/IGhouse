#ifndef IGHOUSE_MECHANISMFACTORY_HPP
#define IGHOUSE_MECHANISMFACTORY_HPP

#include <memory>
#include "MechanismInterface.hpp"
#include "../Utils/TypeDefinitions.hpp"
#include "../sensor/SensorInterface.hpp"

namespace IGHouse
{
namespace Mechanism
{

struct MechanismFactory
{
    static std::shared_ptr<MechanismInterface> createMechanismDriver(MechanismType mechanismType,std::shared_ptr<Sensor::SensorInterface> sensorDrv);
};

}//namespace Mechanism
}//namespace IGHouse

#endif //IGHOUSE_MECHANISMFACTORY_HPP
