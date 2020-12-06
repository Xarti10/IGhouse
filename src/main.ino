#include "Arduino.h"
#include <Wire.h>
#include "sensor/drv/LightSensor.hpp"
#include <memory>
#include "sensor/drv/TemperatureSensor.hpp"
#include "Greenhouse.hpp"
#include "Utils/TypeDefinitions.hpp"
#include "FreeRTOS.h"

//std::unique_ptr<IGHouse::Sensor::Drv::LightSensor> lightSensor;
//std::unique_ptr<IGHouse::Sensor::Drv::TemperatureSensor> temperatureSensor;

// #define WATER_LVL_SENSOR_PIN 19

std::unique_ptr<IGHouse::Greenhouse> iGHouse;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    iGHouse.reset(new IGHouse::Greenhouse);
    pinMode(18, OUTPUT);
    // pinMode(15, OUTPUT);
    delay(5000);
    iGHouse->runMeasurements();
}

int Liquid_level = 0;
bool switcher = false;

void loop()
{
    digitalWrite(18, HIGH);
    delay(2000);
    digitalWrite(18, LOW);
}