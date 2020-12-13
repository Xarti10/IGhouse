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

    if(sensorReadingValue < 20)
    {
        for (int i = 0; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(255, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 20 && sensorReadingValue < 30)
    {
        waterLevelIndicator->setPixelColor(1, waterLevelIndicator->Color(255, 0, 0));
        for (int i = 1; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 30 && sensorReadingValue < 40)
    {
        waterLevelIndicator->setPixelColor(0, waterLevelIndicator->Color(255, 0, 0));
        waterLevelIndicator->setPixelColor(1, waterLevelIndicator->Color(255, 0, 0));
        for (int i = 2; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
    }
    else if(sensorReadingValue >= 40  && sensorReadingValue < 50 )
    {
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
    else if(sensorReadingValue >= 50  && sensorReadingValue < 60)
    {
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
    else if( sensorReadingValue >= 60 && sensorReadingValue < 70)
    {
        for (int i = 0; i < 5; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(255, 255, 0));
        }
        for (int i = 5; i < 8; ++i)
        {
            waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
            waterLevelIndicator->show();
        }
        if(sensorReadingValue >= 70 && sensorReadingValue < 80)
        {
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
        else if(sensorReadingValue >= 80 && sensorReadingValue < 90)
        {
            for (int i = 0; i < 7; ++i)
            {
                waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 255, 0));
            }
            for (int i = 3; i < 8; ++i)
            {
                waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 0, 0));
                waterLevelIndicator->show();
            }
        }
        else
        {
            for (int i = 0; i < 8; ++i)
            {
                waterLevelIndicator->setPixelColor(i, waterLevelIndicator->Color(0, 255, 0));
                waterLevelIndicator->show();
            }
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
    waterLevelIndicator->setBrightness(75);
}


}//namespace Drv
}//namespace Mechanism
}//namespace IGHouse
