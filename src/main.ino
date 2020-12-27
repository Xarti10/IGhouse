#include "Arduino.h"
#include <Wire.h>
#include <memory>
#include "Greenhouse.hpp"

std::unique_ptr<IGHouse::Greenhouse> iGHouse;


void setup()
{
    Serial.begin(9600);
    Wire.begin();
    iGHouse.reset(new IGHouse::Greenhouse);
    delay(500);
    iGHouse->runMeasurements();
}

void loop()
{
    Serial.print("Free heap size: ");
    Serial.print(esp_get_free_heap_size());
    Serial.print(", Minimal free heap size: ");
    Serial.println(esp_get_minimum_free_heap_size());

    delay(5000);
}