#ifndef IGHOUSE_SENSOR_HPP
#define IGHOUSE_SENSOR_HPP

#include "../Utils/TypeDefinitions.h"
#include "../Utils/Measurement.h"
#include "SensorInterface.hpp"
#include <memory>

namespace IGHouse
{
namespace Sensor
{

class Sensor : public SensorInterface
{
public:
    Sensor() = delete;
    explicit Sensor(MeasurementType measType);
    virtual ~Sensor() = default;

    virtual void measure() = 0;
    MeasurementType getMeasurementType() override;
    std::shared_ptr<Measurement> getMeasurement() override;

protected:
    virtual void initSensor() = 0;

private:
    MeasurementType sensorMeasType;
    std::shared_ptr<Measurement> sensorMeas;
};

}//namespace Sensor
}//namespace IGHouse

#endif //IGHOUSE_SENSOR_HPP
