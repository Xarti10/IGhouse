#ifndef IGHOUSE_SPRINKLERMECHANISM_HPP
#define IGHOUSE_SPRINKLERMECHANISM_HPP

#include "../Mechanism.hpp"

namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

class SprinklerMechanism : public Mechanism
{
public:
    SprinklerMechanism() = delete;
    SprinklerMechanism(MechanismType mechType, const std::shared_ptr<Sensor::SensorInterface> &sensorDrv,
                       uint8_t mechPin);
    virtual ~SprinklerMechanism() = default;

    void monitorFunction() override;
    void turnOff() override;
    void turnOn() override;

private:
    void init();
};

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse

#endif //IGHOUSE_SPRINKLERMECHANISM_HPP
