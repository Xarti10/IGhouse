#ifndef IGHOUSE_WATERLEVELINDICATORMECHANISM_HPP
#define IGHOUSE_WATERLEVELINDICATORMECHANISM_HPP

#include "../Mechanism.hpp"

namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

class WaterLevelIndicatorMechanism : public Mechanism
{
public:
    WaterLevelIndicatorMechanism() = delete;
    WaterLevelIndicatorMechanism(MechanismType mechType, const std::shared_ptr<Sensor::SensorInterface> &sensorDrv,
                                 uint8_t mechPin);
    virtual ~WaterLevelIndicatorMechanism() = default;

    void monitorFunction() override;
    void turnOff() override;
    void turnOn() override;

private:
    void init();
};

}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse

#endif //IGHOUSE_WATERLEVELINDICATORMECHANISM_HPP
