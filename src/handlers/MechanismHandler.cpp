#include "MechanismHandler.hpp"
#include "Arduino.h"
#include "FreeRTOS.h"

namespace IGHouse
{
namespace Handlers
{

bool MechanismHandler::isTaskCreated = false;

MechanismHandler::MechanismHandler(std::shared_ptr<MechanismRepository> &mechanismRepository,
                                   std::uint32_t stackDepth)
: mechanismRepo(mechanismRepository)
, stackSize(stackDepth)
, taskHandle(nullptr)
{

}

MechanismHandler::~MechanismHandler()
{
    vTaskDelete(taskHandle);
}

void MechanismHandler::runMechanismMonitorTask()
{
    if(!isTaskCreated)
    {
        xTaskCreate(&runMechanismMonitor, "Sensor Measurements", stackSize, this, tskIDLE_PRIORITY, &taskHandle);
        delay(1000);
    }
}

void MechanismHandler::runMechanismMonitor(void *params)
{
    static_cast <MechanismHandler *>(params)->mechanismMonitor();
}

[[noreturn]] void MechanismHandler::mechanismMonitor()
{
    Serial.println("MeasurementHandler task created");
    constexpr TickType_t taskDelay =  pdMS_TO_TICKS(10000);

    while(true)
    {
        vTaskDelay(taskDelay);
        for (const auto &mechanism : mechanismList)
        {
            Serial.println(String("Number of mechanism in vector: " + String(mechanismList.size())));
            if (mechanism == MechanismType::WATER_LEVEL)
            {
                delay(10);
                Serial.println("Water lever indicator monitor function was called");
                delay(10);
            }
            triggerMechanismMonitor(mechanism);
        }
    }
}

void MechanismHandler::triggerMechanismMonitor(MechanismType mechType)
{
    auto mechanism = mechanismRepo->findMechanism(mechType);
    mechanism->monitorFunction();
}

}//namespace Handlers
}//namespace IGHouse
