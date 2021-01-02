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
            Serial.println("LIGHT mechanism created");
            return std::make_shared<Drv::LightMechanism>(mechanismType, sensorDrv, lightMechanismPin);
        case MechanismType::IRRIGATION:
            Serial.println("IRRIGATION mechanism created");
            return std::make_shared<Drv::IrrigationMechanism>(mechanismType, sensorDrv, irrigationMechanismPin);
        case MechanismType::SPRINKLER:
            Serial.println("SPRINKLER mechanism created");
            return std::make_shared<Drv::SprinklerMechanism>(mechanismType, sensorDrv, sprinklerMechanismPin);
        case MechanismType::WATER_LEVEL:
            Serial.println("WATTER_LEVEL mechanism created");
            return std::make_shared<Drv::WaterLevelIndicatorMechanism>(mechanismType, sensorDrv, waterLeverIndicatorPin);
        case MechanismType::UNKNOWN:
            return nullptr;
        default:
            return nullptr;
    }
}

}//namespace Mechanism
}//namespace IGHouse