#include "MeasurementSerializer.hpp"

#include <Arduino.h>
#include <ArduinoJson.h>

#include "TypeDefinitions.hpp"

namespace IGHouse
{

namespace
{

std::map<MeasurementType, String> measTypeToStringMap
{
    {MeasurementType::TEMPERATURE, "Temperature"},
    {MeasurementType::HUMIDIDY, "Humidity"},
    {MeasurementType::LIGHT, "Light"},
    {MeasurementType::WATER_LEVEL,"WaterLevel"},
    {MeasurementType::SOIL_MOISTURE, "SoilMoisture"}
};

String translateMeasurementTypeToString(MeasurementType measType)
{

    auto measurementType = measTypeToStringMap.find(measType);
    if(measurementType != measTypeToStringMap.end())
        return measurementType->second;

    return "";
}

}//namespace

MeasurementSerializer::MeasurementSerializer(std::shared_ptr<SensorRepository> &sensorRepo, std::uint16_t jsonBufferSize)
: sensorRepo(sensorRepo)
, jsonBuffer(jsonBufferSize)
, measurementData("")
{
}

void MeasurementSerializer::generateJsonSerializedMeasurementDataString()
{
    Serial.println(__FUNCTION__);
    measurementData.clear();
    JsonArray measurementArray = jsonBuffer.createNestedArray("Measurements");

    for(auto &item : sensorRepo->getSensorMap())
    {
        JsonObject measurementObject = measurementArray.createNestedObject();
        measurementObject["Type"] = translateMeasurementTypeToString(item.first);
        measurementObject["Value"] = item.second->getMeasurement()->getMeasurementValue();
//        Serial.print("Object " + jsonBuffer.as<String>());
//        measurementArray.add(measurementObject);
    }

    Serial.print("Data to be serialized: ");
    Serial.println(jsonBuffer.as<String>());
    serializeJson(jsonBuffer, measurementData);

    jsonBuffer.clear();
}

const String &MeasurementSerializer::getMeasurementData() const
{
    return measurementData;
}

String MeasurementSerializer::getGeneratedJsonSerializedSensorDataWithApNameString(String &apName)
{
    Serial.println(__FUNCTION__);

    String result;
    jsonBuffer["DeviceName"] = apName;
    JsonArray measurementArray = jsonBuffer.createNestedArray("Measurements");

    for(auto &item : sensorRepo->getSensorMap())
    {
        JsonObject measurementObject = measurementArray.createNestedObject();
        measurementObject["Type"] = translateMeasurementTypeToString(item.first);
        measurementObject["Value"] = item.second->getMeasurement()->getMeasurementValue();
//        Serial.print("Object " + jsonBuffer.as<String>());
//        measurementArray.add(measurementObject);
    }

    Serial.print("Data to be serialized: ");
    Serial.println(jsonBuffer.as<String>());
    serializeJson(jsonBuffer, result);

    return result;
}


}//namespace IGHouse
