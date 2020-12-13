#include "Measurement.hpp"

namespace IGHouse
{

Measurement::Measurement(MeasurementType measType)
        : measurementType(measType), value(0.0)
{
}

MeasurementType Measurement::getMeasurementType()
{
    return measurementType;
}

void Measurement::setMeasurementValue(float val)
{
    value = val;
}

float Measurement::getMeasurementValue() const
{
    return value;
}

}//namespace IGHouse