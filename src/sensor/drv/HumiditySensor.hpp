#ifndef IGHOUSE_HUMIDITYSENSOR_HPP
#define IGHOUSE_HUMIDITYSENSOR_HPP

#include "ShtSensorType.hpp"
#include "../../Utils/TypeDefinitions.hpp"


namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class HumiditySensor : public ShtSensorType
{
public:
    HumiditySensor() = delete;
    explicit HumiditySensor(MeasurementType measType);

    void measure() override;
};

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_HUMIDITYSENSOR_HPP
