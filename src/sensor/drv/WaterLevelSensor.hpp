#ifndef IGHOUSE_WATERLEVELSENSOR_HPP
#define IGHOUSE_WATERLEVELSENSOR_HPP

#include "../Sensor.hpp"
#include <cstdint>

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class WaterLevelSensor : public Sensor
{
public:
    WaterLevelSensor() = delete;
    explicit WaterLevelSensor(MeasurementType measType);
    virtual ~WaterLevelSensor() = default;
    void measure() override;

private:

    static constexpr std::uint16_t sensorMaxRange = 520;
    static constexpr std::uint16_t adcMaxrange = 4095;

    void initSensor();
};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_WATERLEVELSENSOR_HPP
