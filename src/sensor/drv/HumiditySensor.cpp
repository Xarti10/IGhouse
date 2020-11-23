#include "HumiditySensor.hpp"

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

HumiditySensor::HumiditySensor(MeasurementType measType)
: DhtSensorType(measType)
{
}

void HumiditySensor::measure()
{
    dhtSensorGuard.lock();
    float humidity = dhtSensor->readHumidity();
    if (isnan(humidity))
    {
        Serial.println("Failed to read from DHT");
        humidity = 0.0;
    } else
    {
        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.print(" %\n");
    }
    getMeasurement()->setMeasurementValue(humidity);
    delay(10);
    dhtSensorGuard.unlock();
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse