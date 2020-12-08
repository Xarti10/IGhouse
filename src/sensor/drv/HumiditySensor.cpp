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
    if(dhtSensor == nullptr)
    {
        Serial.println("DHT sensor failure");
        getMeasurement()->setMeasurementValue(0.0);
        return;
    }

    dhtSensorGuard.lock();

    float humidity = dhtSensor->readHumidity();

    if (isnan(humidity))
    {
        Serial.println("Failed to read from DHT");
        humidity = 0.0;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    getMeasurement()->setMeasurementValue(humidity);
    delay(10);

    dhtSensorGuard.unlock();
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse