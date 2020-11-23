#ifndef IGHOUSE_WATERLEVERSENSOR_HPP
#define IGHOUSE_WATERLEVERSENSOR_HPP

#include "../Sensor.hpp"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class WaterLeverSensor : public Sensor
{
public:
    WaterLeverSensor() = delete;
    WaterLeverSensor(MeasurementType measType);
    void measure() override;

private:
    void initSensor() override;
};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_WATERLEVERSENSOR_HPP
