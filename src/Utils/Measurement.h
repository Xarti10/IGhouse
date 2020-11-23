#ifndef IGHOUSE_MEASUREMENT_H
#define IGHOUSE_MEASUREMENT_H

#include "TypeDefinitions.h"

namespace IGHouse
{

class Measurement
{
public:
    Measurement() = delete;
    explicit Measurement(MeasurementType measType);
    MeasurementType getMeasurementType();
    void setMeasurementValue(float val);

private:
    MeasurementType measurementType;
    float value;
//TODO add field that will store data format, also add getter/setter to it
};

}//namespace IGHouse
#endif //IGHOUSE_MEASUREMENT_H
