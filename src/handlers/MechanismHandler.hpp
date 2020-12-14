#ifndef SZKLARNIA_MECHANISMHANDLER_HPP
#define SZKLARNIA_MECHANISMHANDLER_HPP

#include "../mechanism/MechanismRepository.hpp"
#include "FreeRTOS.h"

#include <memory>

namespace IGHouse
{
namespace Handlers
{

class MechanismHandler
{
public:
    MechanismHandler() = delete;
    explicit MechanismHandler(std::shared_ptr<MechanismRepository> &mechanismRepository,
                              std::uint32_t stackDepth = configMINIMAL_STACK_SIZE);
    ~MechanismHandler();

    void runMechanismMonitorTask();

    [[noreturn]] void mechanismMonitor();

private:
    std::shared_ptr<MechanismRepository> mechanismRepo;
    std::uint32_t stackSize;
    TaskHandle_t taskHandle;

    static void runMechanismMonitor(void *params);
    void triggerMechanismMonitor(MechanismType mechType);
};

}//namespace Handlers
}//namespace IGHouse




#endif //SZKLARNIA_MECHANISMHANDLER_HPP
