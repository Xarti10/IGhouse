#include "WaterLevelSensor.hpp"
#include "Arduino.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

WaterLevelSensor::WaterLevelSensor(MeasurementType measType)
        : Sensor(measType)
{
    initSensor();
}

void WaterLevelSensor::measure()
{
    float raw_Val = analogRead(waterLeverSensorPin);
    Serial.print("Raw water level: ");
    Serial.println(raw_Val);
    float dist_t = raw_Val * sensorMaxRange / adcMaxrange;
    Serial.print("Water level: ");
    Serial.println(dist_t);
    getMeasurement()->setMeasurementValue(dist_t);
}

void WaterLevelSensor::initSensor()
{
//    pinMode(waterLeverSensorPin, OUTPUT);
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse