#ifndef IGHOUSE_TEMPERATURESENSOR_HPP
#define IGHOUSE_TEMPERATURESENSOR_HPP

#include <memory>
#include "../Sensor.hpp"
#include "ShtSensorType.hpp"
#include "../../Utils/TypeDefinitions.hpp"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class TemperatureSensor : public ShtSensorType
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
