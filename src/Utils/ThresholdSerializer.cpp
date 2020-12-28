#include "ThresholdSerializer.hpp"
#include "PreferenceAdapter.hpp"

namespace IGHouse
{

ThresholdSerializer::ThresholdSerializer(std::uint16_t jsonBufferSize)
: jsonBuffer(jsonBufferSize)
, thresholdData("")
{
}

void ThresholdSerializer::generateJsonSerializedThresholdDataString()
{
    thresholdData.clear();

    JsonArray thresholdArray = jsonBuffer.createNestedArray("Thresholds");

    auto soilMoisture = thresholdArray.createNestedObject();
    auto humidity = thresholdArray.createNestedObject();
    auto light = thresholdArray.createNestedObject();

    soilMoisture["soilMoisture"] = soilMoisture;
    humidity["humidity"] = humidity;
    light["light"] = light;

    serializeJson(jsonBuffer, thresholdData);
}

const String &ThresholdSerializer::getThresholdData() const
{
    return thresholdData;
}

void ThresholdSerializer::deserializeDataAndUpdatePreferences(String data)
{
    deserializeJson(jsonBuffer, data);

    JsonArray Thresholds = jsonBuffer["Thresholds"];

    JsonVariant soilMoistureJson = Thresholds[0]["soilMoisture"];
    JsonVariant humidityJson = Thresholds[0]["humidity"];
    JsonVariant lightJson = Thresholds[0]["light"];

    if(soilMoistureJson.isNull() || humidityJson.isNull() || lightJson.isNull())
    {
        Serial.println("Wrong ssid name was provided");
        return;
    }

    ThresholdsPreferences thresholdsPrefs;
    thresholdsPrefs.soilMoisture = soilMoistureJson.as<float>();
    thresholdsPrefs.humidity = humidityJson.as<float>();
    thresholdsPrefs.light = lightJson.as<float>();

    PreferencesAdapter::setThresholdsPreferences(thresholdsPrefs);
}

String ThresholdSerializer::getGeneratedJsonSerializedThresholdDataWithApNameString(String &apName)
{
    String thresholdDataWithDeviceName;

    jsonBuffer["DeviceName"] = apName;
    JsonArray thresholdArray = jsonBuffer.createNestedArray("Thresholds");

    auto soilMoisture = thresholdArray.createNestedObject();
    auto humidity = thresholdArray.createNestedObject();
    auto light = thresholdArray.createNestedObject();

    soilMoisture["soilMoisture"] = soilMoisture;
    humidity["humidity"] = humidity;
    light["light"] = light;

    serializeJson(jsonBuffer, thresholdDataWithDeviceName);
    return thresholdDataWithDeviceName;
}

}//namespace IGHouse
