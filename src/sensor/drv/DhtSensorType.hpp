#ifndef IGHOUSE_DHTSENSORTYPE_HPP
#define IGHOUSE_DHTSENSORTYPE_HPP

#include <mutex>
#include <memory>
#include "../Sensor.hpp"
#include "DHT.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class DhtSensorType : public Sensor
{
public:
    DhtSensorType() = delete;
    explicit DhtSensorType(MeasurementType measType);
    virtual void measure() = 0;

private:
    void initSensor();
    static bool sensorInited;

protected:
    static std::shared_ptr<DHT> dhtSensor;
    static std::mutex dhtSensorGuard;

};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_DHTSENSORTYPE_HPP
