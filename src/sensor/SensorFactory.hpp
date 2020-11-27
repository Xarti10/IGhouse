#ifndef IGHOUSE_SENSORFACTORY_HPP
#define IGHOUSE_SENSORFACTORY_HPP

#include <memory>
#include "SensorInterface.hpp"

namespace IGHouse
{
namespace Sensor
{

struct SensorFactory
{
    static std::shared_ptr<SensorInterface> createSensorDriver(MeasurementType measType);
};

}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_SENSORFACTORY_HPP
