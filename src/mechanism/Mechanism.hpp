#ifndef IGHOUSE_MECHANISM_HPP
#define IGHOUSE_MECHANISM_HPP

#include <cstdint>

#include "MechanismInterface.hpp"
#include "../sensor/SensorInterface.hpp"

namespace IGHouse
{
namespace Mechanism
{

class Mechanism : public MechanismInterface
{
public:
    Mechanism() = delete;
    explicit Mechanism(MechanismType mechType,std::shared_ptr<Sensor::SensorInterface> sensorDrv, std::uint8_t mechPin);
    virtual ~Mechanism() = default;

    virtual void runObservation() = 0;
    virtual void turnOff() = 0;
    virtual void turnOn() = 0;

protected:
    virtual void init() = 0;

private:
    MechanismType mechanismType;
    std::shared_ptr<Sensor::SensorInterface> sensor;
    std::uint8_t mechanismPin;

};

}//namespace Mechanism
}//namespace IGHouse

#endif //IGHOUSE_MECHANISM_HPP
