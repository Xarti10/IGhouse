#ifndef IGHOUSE_LIGHTMECHANISM_HPP
#define IGHOUSE_LIGHTMECHANISM_HPP

#include "../Mechanism.hpp"

namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

class LightMechanism : public Mechanism
{
public:
    LightMechanism() = delete;
    LightMechanism(MechanismType mechType, const std::shared_ptr<Sensor::SensorInterface> &sensorDrv, uint8_t mechPin);
    virtual ~LightMechanism() = default;

    void monitorFunction() override;
    void turnOff() override;
    void turnOn() override;

private:
    void init();
};

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse

#endif //IGHOUSE_LIGHTMECHANISM_HPP
