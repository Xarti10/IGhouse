#ifndef SZKLARNIA_THRESHOLDSERIALIZER_HPP
#define SZKLARNIA_THRESHOLDSERIALIZER_HPP

#include <memory>
#include <Arduino.h>
#include <ArduinoJson.h>

#include "../sensor/SensorRepository.hpp"

namespace IGHouse
{

class ThresholdSerializer
{
public:
    explicit ThresholdSerializer(std::uint16_t jsonBufferSize = 256);
    ~ThresholdSerializer() = default;

    void generateJsonSerializedThresholdDataString();
    String getGeneratedJsonSerializedThresholdDataWithApNameString(String &apName);
    const String &getThresholdData() const;
    void deserializeDataAndUpdatePreferences(String data);

private:
    DynamicJsonDocument jsonBuffer;
    String thresholdData;
};

}//namespace IGHouse

#endif //SZKLARNIA_THRESHOLDSERIALIZER_HPP
