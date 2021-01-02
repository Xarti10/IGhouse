#include "WaterLevelIndicatorMechanism.hpp"
#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include <memory>
#include <Utils/PinDefinitions.hpp>


namespace IGHouse
{
namespace Mechanism
{
namespace Drv
{

WaterLevelIndicatorMechanism::WaterLevelIndicatorMechanism(MechanismType mechType,
                                                           const std::shared_ptr<Sensor::SensorInterface> &sensorDrv,
                                                           uint8_t mechPin)
: Mechanism(mechType, sensorDrv, mechPin)
, waterLevelIndicator(std::make_shared<Adafruit_NeoPixel>(8, waterLeverIndicatorPin))
{
    init();
}

void WaterLevelIndicatorMechanism::monitorFunction()
{
    auto sensorReadingValue = sensor->getMeasurement()->getMeasurementValue();

    Serial.print("Water level value in water level monitor function: ");
    Serial.println(sensorReadingValue);
    delay(50);
    if(sensorReadingValue < 20.0f)
    {
        Serial.print("Case 1 ");
        Serial.println(sensorReadingValue);
        delay(50);
        for (int i = 0; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(255, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 20.0f && sensorReadingValue < 30.0f)
    {
        Serial.print("Case 2 ");
        Serial.println(sensorReadingValue);
        delay(50);
        waterLevelIndicator->setPixelColor(0, waterLevelIndicator->Color(255, 0, 0));
        for (int i = 1; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 30.0f && sensorReadingValue < 40.0f)
    {
        Serial.print("Case 3 ");
        Serial.println(sensorReadingValue);
        delay(50);
        waterLevelIndicator->setPixelColor(0, waterLevelIndicator->Color(255, 0, 0));
        waterLevelIndicator->setPixelColor(1, waterLevelIndicator->Color(255, 0, 0));
        for (int i = 2; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 40.0f  && sensorReadingValue < 50.0f )
    {
        Serial.print("Case 4 ");
        Serial.println(sensorReadingValue);
        delay(50);
        for (int i = 0; i < 3; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(255, 255, 0));
        }
        for (int i = 3; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 50.0f  && sensorReadingValue < 60.0f)
    {
        Serial.print("Case 5 ");
        Serial.println(sensorReadingValue);
        delay(50);
        for (int i = 0; i < 4; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(255, 255, 0));
        }
        for (int i = 4; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if( sensorReadingValue >= 60.0f && sensorReadingValue < 70.0f)
    {
        Serial.print("Case 6 ");
        Serial.println(sensorReadingValue);
        delay(50);
        for (int i = 0; i < 5; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(255, 255, 0));
        }
        for (int i = 5; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 70.0f && sensorReadingValue < 80.0f)
    {
        Serial.print("Case 7 ");
        Serial.println(sensorReadingValue);
        delay(50);
        for (int i = 0; i < 6; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(255, 255, 0));
        }
        for (int i = 6; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 80.0f && sensorReadingValue < 90.0f)
    {
        Serial.print("Case 8 ");
        Serial.println(sensorReadingValue);
        delay(50);
        for (int i = 0; i < 7; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 255, 0));
        }
        for (int i = 7; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else
    {
        Serial.print("Case 9 ");
        Serial.println(sensorReadingValue);
        delay(50);
        for (int i = 0; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 255, 0));
            waterLevelIndicator->show();
        }
    }
}


void WaterLevelIndicatorMechanism::turnOff()
{
}

void WaterLevelIndicatorMechanism::turnOn()
{
}

void WaterLevelIndicatorMechanism::init()
{
    waterLevelIndicator->begin();
    waterLevelIndicator->setBrightness(30);
}


}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse
