#include "TemperatureSensor.hpp"
#include "../../Utils/TypeDefinitions.hpp"
#include "Arduino.h"
#include "SHTSensor.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

TemperatureSensor::TemperatureSensor(MeasurementType measType)
: ShtSensorType(measType)
{
}

void TemperatureSensor::measure()
{
    if(shtSensor == nullptr)
    {
        Serial.println("DHT sensor failure");
        getMeasurement()->setMeasurementValue(0.0);
        return;
    }

    shtSensorGuard.lock();

    float temperature = shtSensor->getTemperature();

    if (isnan(temperature))
    {
        Serial.println("Failed to read from sensor");
        temperature = 0.0;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");

    getMeasurement()->setMeasurementValue(temperature);
    delay(10);

    shtSensorGuard.unlock();
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse