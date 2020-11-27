#include "Arduino.h"
#include <Wire.h>
#include "sensor/drv/LightSensor.hpp"
#include <memory>
#include "sensor/drv/TemperatureSensor.hpp"
#include "Greenhouse.hpp"
#include "Utils/TypeDefinitions.hpp"

//std::unique_ptr<IGHouse::Sensor::Drv::LightSensor> lightSensor;
//std::unique_ptr<IGHouse::Sensor::Drv::TemperatureSensor> temperatureSensor;

// #define WATER_LVL_SENSOR_PIN 19

std::unique_ptr<IGHouse::Greenhouse> iGHouse;

void setup()
{
    Serial.begin(9600);
    iGHouse.reset(new IGHouse::Greenhouse);
//    Wire.begin();
//    lightSensor.reset(new IGHouse::Sensor::Drv::LightSensor(IGHouse::MeasurementType::LIGHT));
//    temperatureSensor.reset(new IGHouse::Sensor::Drv::TemperatureSensor(IGHouse::MeasurementType::TEMPERATURE));
//    pinMode(18, OUTPUT);
    // pinMode(15, OUTPUT);
}

int Liquid_level = 0;
bool switcher = false;

void loop()
{
//    lightSensor->measure();
//    delay(100);
//    temperatureSensor->measure();
//    digitalWrite(18, switcher ? HIGH : LOW);
//    Serial.print("Diode status: "); Serial.print(switcher);
//    Serial.print("\n");
//    // Serial.print("Liquid_level= ");Serial.println(Liquid_level,DEC);
//    delay(3000);
//    switcher = !switcher;
}