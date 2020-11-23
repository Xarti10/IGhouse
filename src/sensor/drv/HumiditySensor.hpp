#ifndef IGHOUSE_HUMIDITYSENSOR_HPP
#define IGHOUSE_HUMIDITYSENSOR_HPP

#include "DhtSensorType.hpp"
#include "../../Utils/TypeDefinitions.h"


namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

class HumiditySensor : public DhtSensorType
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
