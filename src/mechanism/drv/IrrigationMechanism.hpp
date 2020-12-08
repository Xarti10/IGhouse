#ifndef IGHOUSE_IRRIGATIONMECHANISM_HPP
#define IGHOUSE_IRRIGATIONMECHANISM_HPP

#include "../Mechanism.hpp"

namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

class IrrigationMechanism : public Mechanism
{
public:
    IrrigationMechanism() = delete;
    IrrigationMechanism(MechanismType mechType, const std::shared_ptr<Sensor::SensorInterface> &sensorDrv,
                        uint8_t mechPin);
    virtual ~IrrigationMechanism() = default;

    void monitorFunction() override;
    void turnOff() override;
    void turnOn() override;

private:
    void init();
};

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse

#endif //IGHOUSE_IRRIGATIONMECHANISM_HPP
