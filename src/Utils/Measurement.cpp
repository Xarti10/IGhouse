#include "Measurement.hpp"

namespace IGHouse
{

Measurement::Measurement(MeasurementType measType)
        : measurementType(measType), value(0.0)
{
//TODO make implementation in needed
}

MeasurementType Measurement::getMeasurementType()
{
    return measurementType;
}

void Measurement::setMeasurementValue(float val)
{
    value = val;
}

}//namespace IGHouse