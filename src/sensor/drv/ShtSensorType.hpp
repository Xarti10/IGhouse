#ifndef IGHOUSE_DHTSENSORTYPE_HPP
#define IGHOUSE_DHTSENSORTYPE_HPP

#include <mutex>
#include <memory>
#include "../Sensor.hpp"
#include "SHTSensor.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class ShtSensorType : public Sensor
{
public:
    ShtSensorType() = delete;
    explicit ShtSensorType(MeasurementType measType);
    virtual void measure() = 0;

private:
    void initSensor();
    static bool sensorInited;

protected:
    static std::shared_ptr<SHTSensor> shtSensor;
    static std::mutex shtSensorGuard;

};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_DHTSENSORTYPE_HPP
