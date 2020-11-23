#ifndef IGHOUSE_TEMPERATURESENSOR_HPP
#define IGHOUSE_TEMPERATURESENSOR_HPP

#include "DHT.h"
#include <memory>
#include "../Sensor.hpp"
#include "DhtSensorType.hpp"
#include "../../Utils/TypeDefinitions.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class TemperatureSensor : public DhtSensorType
{
public:
    TemperatureSensor() = delete;
    explicit TemperatureSensor(MeasurementType measType);

    void measure() override;
};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_TEMPERATURESENSOR_HPP
