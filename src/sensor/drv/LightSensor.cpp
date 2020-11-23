#include "LightSensor.hpp"
#include <Wire.h>

namespace IGHouse
{
namespace Sensor
{
namespace Drv
{

LightSensor::LightSensor(MeasurementType measType)
: Sensor(measType)
, tslSensor(nullptr)
{
    initSensor();
}

void LightSensor::checkId()
{
    int id;
    int a;
    id = tslSensor->TSL2581_Read_ID();
    a = id & 0xf0;      //The lower four bits are the silicon version number
    if (!(a == 144))    //ID = 90H = 144D
    {
        Serial.println("false ");
        correctSensorId = false;
    }
    else
    {
        Serial.print("I2C DEV is working, id = ");
        Serial.println(id);
        correctSensorId = true;
        delay(500);
    }
}

void LightSensor::initSensor()
{
    tslSensor.reset(new WaveShare_TSL2581());
    checkId();

    tslSensor->TSL2581_power_on();
    delay(2000);
    tslSensor->TSL2581_config();
}

void LightSensor::measure()
{
    tslSensor->TSL2581_Read_Channel();

    Serial.print("Lux = " );
    Serial.print(tslSensor->calculateLux(2, NOM_INTEG_CYCLE));
    Serial.print("\n");
}

}//namespace Drv
}//namespace Sensor
}//namespace IGHouse