#include "MeasurementHandler.hpp"
#include "FreeRTOS.h"
#include "Arduino.h"
#include <string>
#include <Utils/MeasurementSerializer.hpp>

namespace IGHouse
{
namespace Handlers
{

MeasurementHandler::MeasurementHandler(std::shared_ptr<SensorRepository> &sensorRepo,
                                       std::shared_ptr<MeasurementSerializer> &measurementSerializer,
                                       std::uint32_t stackDepth)
: sensorRepo(sensorRepo)
, measSerializer(measurementSerializer)
, stackSize(stackDepth)
, taskHandle(nullptr)
{
}

MeasurementHandler::~MeasurementHandler()
{
    vTaskDelete(taskHandle);
}

void MeasurementHandler::runMeasuremenentTask()
{
    xTaskCreate(&runMeasurements, "Sensor Measurements", stackSize, this, tskIDLE_PRIORITY, &taskHandle);
    delay(1500);
}

void MeasurementHandler::runMeasurements(void *params)
{
    static_cast <MeasurementHandler *>(params)->measurements();
//    std::shared_ptr<MeasurementHandler> measurementHandlerClassPointer((MeasurementHandler *) params);
//    measurementHandlerClassPointer->measurements();
}

[[noreturn]] void MeasurementHandler::measurements()
{
    Serial.println();
    Serial.println("MeasurementHandler task created");
    constexpr TickType_t taskDelay = 5000 / portTICK_PERIOD_MS;

    while(true)
    {
        Serial.println("Measurements started");
        for (const auto &measurement : measurementList)
        {
            triggerSensorMeasurement(measurement);
        }
        measSerializer->generateJsonSerializedMeasurementDataString();
        vTaskDelay(taskDelay);
    }
}

void MeasurementHandler::triggerSensorMeasurement(MeasurementType measType)
{
    auto sensor = sensorRepo->findSensor(measType);
    sensor->measure();
}


}//namespace Handlers
}//namespace IGHouse