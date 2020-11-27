#ifndef IGHOUSE_SENSORINTERFACE_HPP
#define IGHOUSE_SENSORINTERFACE_HPP

#include "../Utils/TypeDefinitions.hpp"
#include "../Utils/Measurement.hpp"
#include <memory>

namespace IGHouse
{
namespace Sensor
{

class SensorInterface
{
public:
    SensorInterface() = default;

    virtual ~SensorInterface() = default;

    virtual void measure() = 0;
    virtual std::shared_ptr<Measurement> getMeasurement() = 0;
    virtual MeasurementType getMeasurementType() = 0;

protected:
    virtual void initSensor() = 0;
};

}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_SENSORINTERFACE_HPP
