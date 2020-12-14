#include "MechanismHandler.hpp"
#include "Arduino.h"
#include "FreeRTOS.h"

namespace IGHouse
{
namespace Handlers
{


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
    xTaskCreate(&runMechanismMonitor, "Sensor Measurements", stackSize, this, tskIDLE_PRIORITY, &taskHandle);
    delay(1000);
}

void MechanismHandler::runMechanismMonitor(void *params)
{
    static_cast <MechanismHandler *>(params)->mechanismMonitor();
}

[[noreturn]] void MechanismHandler::mechanismMonitor()
{
    Serial.println("MeasurementHandler task created");
    constexpr TickType_t taskDelay = 10000 / portTICK_PERIOD_MS;

    while(true)
    {
        for (const auto &mechanism : mechanismList)
        {
            triggerMechanismMonitor(mechanism);
        }

        vTaskDelay(taskDelay);
    }
}

void MechanismHandler::triggerMechanismMonitor(MechanismType mechType)
{
    auto mechanism = mechanismRepo->findMechanism(mechType);
    mechanism->monitorFunction();
}

}//namespace Handlers
}//namespace IGHouse
