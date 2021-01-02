#include "MechanismRepository.hpp"
#include "MechanismFactory.hpp"

#include <map>
#include <memory>

namespace IGHouse
{

MechanismRepository::MechanismRepository(std::shared_ptr<SensorRepository> sensorRepository)
: sensorRepo(sensorRepository)
, mechanismMap()
{
    createMechanisms();
}

MechanismRepository::MechanismRepositoryMap MechanismRepository::getMechanismMap()
{
    return mechanismMap;
}

std::shared_ptr<Mechanism::MechanismInterface> MechanismRepository::findMechanism(MechanismType mechanismType)
{
    auto mechanismFind = mechanismMap.find(mechanismType);
    if (mechanismFind != mechanismMap.end())
        return mechanismFind->second;
    else
        return nullptr;
}

std::shared_ptr<Sensor::SensorInterface> MechanismRepository::mapSensorToMechanism(MechanismType mechanismType)
{
    switch (mechanismType)
    {
        case MechanismType::LIGHT:
            return sensorRepo->findSensor(MeasurementType::LIGHT);
        case MechanismType::IRRIGATION:
            return sensorRepo->findSensor(MeasurementType::SOIL_MOISTURE);
        case MechanismType::SPRINKLER:
            return sensorRepo->findSensor(MeasurementType::HUMIDIDY);
        case MechanismType::WATER_LEVEL:
            return sensorRepo->findSensor(MeasurementType::WATER_LEVEL);
        case MechanismType::UNKNOWN:
        default:
            return nullptr;
    }
}

void MechanismRepository::createMechanisms()
{
    using namespace Mechanism;
    typedef std::pair<MechanismType, std::shared_ptr<MechanismInterface>> MechanismPair;

    for (const auto &mechanismTypeIt : mechanismList)
    {
        mechanismMap.insert(MechanismPair (mechanismTypeIt, MechanismFactory::createMechanismDriver(mechanismTypeIt,
                                                                                                    mapSensorToMechanism(mechanismTypeIt))));
    }
}


}//namespace IGHouse