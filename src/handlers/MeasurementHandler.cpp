#include "MeasurementHandler.hpp"
#include "FreeRTOS.h"
#include "Arduino.h"
#include <string>

namespace IGHouse
{
namespace Handlers
{

MeasurementHandler::MeasurementHandler(std::shared_ptr<SensorRepository> sensorRepo, std::uint32_t stackDepth)
: sensorRepo(sensorRepo)
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
    Serial.println("MeasurementHandler task created");
    constexpr TickType_t taskDelay = 1000 / portTICK_PERIOD_MS;

    while(true)
    {
        triggerSensorMeasurement(MeasurementType::LIGHT);
        triggerSensorMeasurement(MeasurementType::WATER_LEVEL);
        triggerSensorMeasurement(MeasurementType::HUMIDIDY);
        triggerSensorMeasurement(MeasurementType::TEMPERATURE);
        triggerSensorMeasurement(MeasurementType::SOIL_MOISTURE);

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