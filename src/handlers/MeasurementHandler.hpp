#ifndef IGHOUSE_MEASUREMENTHANDLER_HPP
#define IGHOUSE_MEASUREMENTHANDLER_HPP

#include <memory>
#include "../sensor/SensorRepository.hpp"
#include "FreeRTOS.h"

namespace IGHouse
{
namespace Handlers
{

class MeasurementHandler
{
public:
    MeasurementHandler() = delete;
    explicit MeasurementHandler(std::shared_ptr<SensorRepository> &sensorRepo,
                                std::uint32_t stackDepth = configMINIMAL_STACK_SIZE);
    ~MeasurementHandler();

    void runMeasuremenentTask();

    [[noreturn]] [[noreturn]] void measurements();

private:
    std::shared_ptr<SensorRepository> sensorRepo;
    std::uint32_t stackSize;
    TaskHandle_t taskHandle;

    static void runMeasurements(void *params);
    void triggerSensorMeasurement(MeasurementType measType);
};

}//namespace Handlers
}//namespace IGHouse

#endif //IGHOUSE_MEASUREMENTHANDLER_HPP
