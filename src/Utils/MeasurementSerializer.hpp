#ifndef SZKLARNIA_MEASUREMENTSERIALIZER_HPP
#define SZKLARNIA_MEASUREMENTSERIALIZER_HPP

#include <memory>
#include <Arduino.h>
#include <ArduinoJson.h>

#include "../sensor/SensorRepository.hpp"

namespace IGHouse
{

class MeasurementSerializer
{
public:
    MeasurementSerializer() = delete;
    explicit MeasurementSerializer(std::shared_ptr<SensorRepository> &sensorRepo, std::uint16_t jsonBufferSize = 256);
    ~MeasurementSerializer() = default;

    void generateJsonSerializedMeasurementDataString();
    String getGeneratedJsonSerializedSensorDataWithApNameString(String &apName);
    const String &getMeasurementData() const;

private:
    std::shared_ptr<SensorRepository> sensorRepo;
    DynamicJsonDocument jsonBuffer;
    String measurementData;
};

}//namespace IGHouse

#endif //SZKLARNIA_MEASUREMENTSERIALIZER_HPP
