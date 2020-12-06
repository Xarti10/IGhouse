#ifndef IGHOUSE_SOILMOISTURESENSOR_HPP
#define IGHOUSE_SOILMOISTURESENSOR_HPP

#include "../Sensor.hpp"

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
    void initSensor();

};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse


#endif //IGHOUSE_SOILMOISTURESENSOR_HPP
