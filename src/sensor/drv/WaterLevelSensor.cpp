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
    float raw_Val = 0.0;
    for (int i = 0; i < 100; ++i)
    {
        raw_Val += analogRead(waterLeverSensorPin);
    }

    Serial.print("Raw water level: ");
    Serial.println(18 - ((raw_Val / 100) * ((float)sensorMaxRange / (float)adcMaxrange)) / 3);
    float dist_t = (18 - ((raw_Val / 100) * ((float)sensorMaxRange / (float)adcMaxrange)) / 3) / 18 * 100;
    Serial.print("Water level: ");
    Serial.print(dist_t);
    Serial.println("%");
    getMeasurement()->setMeasurementValue(dist_t);
}

void WaterLevelSensor::initSensor()
{
//    pinMode(waterLeverSensorPin, OUTPUT);
    analogSetPinAttenuation(waterLeverSensorPin, ADC_0db);

}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse