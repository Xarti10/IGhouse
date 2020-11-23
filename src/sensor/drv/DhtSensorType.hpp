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
    static constexpr std::uint8_t dhtPin = 15;

    void initSensor() override;

protected:
    static std::mutex dhtSensorGuard;
    std::shared_ptr<DHT> dhtSensor{};

};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_DHTSENSORTYPE_HPP
