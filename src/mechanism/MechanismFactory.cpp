#include "MechanismFactory.hpp"
#include "../sensor/SensorInterface.hpp"
#include "drv/LightMechanism.hpp"
#include "drv/IrrigationMechanism.hpp"
#include "drv/SprinklerMechanism.hpp"
#include "drv/WaterLevelIndicatorMechanism.hpp"
#include "../Utils/PinDefinitions.hpp"

#include <memory>

namespace IGHouse
{
namespace Mechanism
{

std::shared_ptr<MechanismInterface> MechanismFactory::createMechanismDriver(MechanismType mechanismType,
                                                                            std::shared_ptr<Sensor::SensorInterface> sensorDrv)
{
    switch(mechanismType)
    {
        case MechanismType::LIGHT:
            return std::make_shared<Drv::LightMechanism>(mechanismType, sensorDrv, lightPin);
        case MechanismType::IRRIGATION:
            return std::make_shared<Drv::IrrigationMechanism>(mechanismType, sensorDrv, irrigationPin);
        case MechanismType::SPRINKLER:
            return std::make_shared<Drv::SprinklerMechanism>(mechanismType, sensorDrv, sprinklerPin);
        case MechanismType::WATTER_LEVEL:
            return std::make_shared<Drv::WaterLevelIndicatorMechanism>(mechanismType, sensorDrv, waterLeverIndicatorPin);
        case MechanismType::UNKNOWN:
            return nullptr;
        default:
            return nullptr;
    }
}

}//namespace Mechanism
}//namespace IGHouse