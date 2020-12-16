#include "SensorFactory.hpp"
#include "SensorInterface.hpp"
#include "drv/LightSensor.hpp"
#include "drv/WaterLevelSensor.hpp"
#include "drv/HumiditySensor.hpp"
#include "drv/TemperatureSensor.hpp"
#include "drv/SoilMoistureSensor.hpp"

#include <memory>

namespace IGHouse
{
namespace Sensor
{

std::shared_ptr<SensorInterface> SensorFactory::createSensorDriver(MeasurementType measType)
{
    switch(measType)
    {
        case MeasurementType::LIGHT:
            Serial.println("LIGHT measurement created");
            return std::make_shared<Drv::LightSensor>(measType);
        case MeasurementType::WATER_LEVEL:
            Serial.println("WATER_LEVEL measurement created");
            return std::make_shared<Drv::WaterLevelSensor>(measType);
        case MeasurementType::HUMIDIDY:
            Serial.println("HUMIDIDY measurement created");
            return std::make_shared<Drv::HumiditySensor>(measType);
        case MeasurementType::TEMPERATURE:
            Serial.println("TEMPERATURE measurement created");
            return std::make_shared<Drv::TemperatureSensor>(measType);
        case MeasurementType::SOIL_MOISTURE:
            Serial.println("SOIL_MOISTURE measurement mechanism created");
            return std::make_shared<Drv::SoilMoistureSensor>(measType);
        case MeasurementType::CRITICAL_WATTER_LEVEL:
        case MeasurementType::UNKNOWN:
        default:
            return nullptr;
    }
}

}//namespace Sensor
}//namespace IGHouse