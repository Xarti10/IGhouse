#include "TemperatureSensor.hpp"
#include "../../Utils/TypeDefinitions.hpp"
#include "DHT.h"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

TemperatureSensor::TemperatureSensor(MeasurementType measType)
: DhtSensorType(measType)
{
}

void TemperatureSensor::measure()
{
    dhtSensorGuard.lock();
    float temperature = dhtSensor->readTemperature();
    if (isnan(temperature))
    {
        Serial.println("Failed to read from DHT");
        temperature = 0.0;
    } else
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" *C\n");
    }
    getMeasurement()->setMeasurementValue(temperature);
    delay(10);
    dhtSensorGuard.unlock();
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse