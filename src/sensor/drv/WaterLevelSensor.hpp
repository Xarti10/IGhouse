#ifndef IGHOUSE_WATERLEVELSENSOR_HPP
#define IGHOUSE_WATERLEVELSENSOR_HPP

#include "../Sensor.hpp"

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
    WaterLevelSensor(MeasurementType measType);
    void measure() override;

private:
    void initSensor() override;
};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_WATERLEVELSENSOR_HPP
