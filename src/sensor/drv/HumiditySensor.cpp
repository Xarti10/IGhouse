#include "HumiditySensor.hpp"
#include "Arduino.h"
#include "SHTSensor.h"


namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

HumiditySensor::HumiditySensor(MeasurementType measType)
: ShtSensorType(measType)
{
}

void HumiditySensor::measure()
{
    if(shtSensor == nullptr)
    {
        Serial.println("DHT sensor failure");
        getMeasurement()->setMeasurementValue(0.0);
        return;
    }

    shtSensorGuard.lock();

    float humidity = shtSensor->getHumidity();

    if (isnan(humidity))
    {
        Serial.println("Failed to read from sensor");
        humidity = 0.0;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    getMeasurement()->setMeasurementValue(humidity);
    delay(10);

    shtSensorGuard.unlock();
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse