#ifndef IGHOUSE_LIGHTSENSOR_HPP
#define IGHOUSE_LIGHTSENSOR_HPP

#include "TSL2581.h"
#include <memory>
#include "../Sensor.hpp"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class LightSensor : public Sensor
{
public:
    LightSensor() = delete;
    explicit LightSensor(MeasurementType measType);

    void measure() override;

private:
    void checkId();

    std::unique_ptr<WaveShare_TSL2581> tslSensor;
    bool correctSensorId;
    void initSensor() ;

};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_LIGHTSENSOR_HPP
