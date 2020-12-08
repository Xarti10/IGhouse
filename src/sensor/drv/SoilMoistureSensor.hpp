#ifndef IGHOUSE_SOILMOISTURESENSOR_HPP
#define IGHOUSE_SOILMOISTURESENSOR_HPP

#include "../Sensor.hpp"
#include <cstdint>

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class SoilMoistureSensor : public Sensor
{
public:
    SoilMoistureSensor() = delete;
    explicit SoilMoistureSensor(MeasurementType measType);

    void measure() override;

private:
    static constexpr std::uint16_t drySensorInAir = 3000;
    static constexpr std::uint16_t wetSensorInWater = 1320;
    void initSensor();

};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse


#endif //IGHOUSE_SOILMOISTURESENSOR_HPP
