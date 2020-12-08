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
    if(dhtSensor == nullptr)
    {
        Serial.println("DHT sensor failure");
        getMeasurement()->setMeasurementValue(0.0);
        return;
    }

    dhtSensorGuard.lock();

    float temperature = dhtSensor->readTemperature();

    if (isnan(temperature))
    {
        Serial.println("Failed to read from DHT");
        temperature = 0.0;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");

    getMeasurement()->setMeasurementValue(temperature);
    delay(10);

    dhtSensorGuard.unlock();
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse