#include "Arduino.h"
#include <Wire.h>
#include "sensor/drv/LightSensor.hpp"
#include <memory>
#include "sensor/drv/TemperatureSensor.hpp"
#include "Greenhouse.hpp"
#include "Utils/TypeDefinitions.hpp"
#include "FreeRTOS.h"
#include "Utils/PinDefinitions.hpp"

std::unique_ptr<IGHouse::Greenhouse> iGHouse;


void setup()
{
//    analogSetAttenuation(ADC_0db);
    Serial.begin(9600);
    Wire.begin();
    iGHouse.reset(new IGHouse::Greenhouse);
    delay(500);
    iGHouse->runMeasurements();
}

void loop()
{

}