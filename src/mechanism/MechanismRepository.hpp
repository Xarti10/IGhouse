#ifndef IGHOUSE_MECHANISMREPOSITORY_HPP
#define IGHOUSE_MECHANISMREPOSITORY_HPP

#include <memory>
#include "../sensor/SensorRepository.hpp"
#include "MechanismInterface.hpp"
#include <map>
#include "../Utils/TypeDefinitions.hpp"
#include "../sensor/SensorInterface.hpp"

namespace IGHouse
{

class MechanismRepository
{
public:
    MechanismRepository() = delete;
    explicit MechanismRepository(std::shared_ptr<SensorRepository> sensorRepository);

    typedef std::map<MechanismType, std::shared_ptr<Mechanism::MechanismInterface>> MechanismRepositoryMap;
    MechanismRepositoryMap getMechanismMap();
    std::shared_ptr<Mechanism::MechanismInterface> findMechanism(MechanismType mechanismType);

private:
    std::shared_ptr<SensorRepository> sensorRepo;
    MechanismRepositoryMap mechanismMap;

    std::shared_ptr<Sensor::SensorInterface> mapSensorToMechanism(MechanismType mechanismType);
    void createMechanisms();
};

}

#endif //IGHOUSE_MECHANISMREPOSITORY_HPP
