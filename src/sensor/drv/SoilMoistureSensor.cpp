#include "SoilMoistureSensor.hpp"
#include "Arduino.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{


SoilMoistureSensor::SoilMoistureSensor(MeasurementType measType)
: Sensor(measType)
{
    initSensor();
}

void SoilMoistureSensor::measure()
{
    float rawVal = analogRead(soilMoistureSensorPin);
    float soilHumidity = (roundf((100 - (rawVal - wetSensorInWater)/(float(drySensorInAir-wetSensorInWater)/100)) * 100))/100;
    Serial.print("Soil moisture: ");
    Serial.print(soilHumidity);
    Serial.println("%");

    getMeasurement()->setMeasurementValue(soilHumidity);
}

void SoilMoistureSensor::initSensor()
{
//    TODO implement
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse