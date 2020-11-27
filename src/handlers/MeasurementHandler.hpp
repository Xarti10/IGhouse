#ifndef IGHOUSE_MEASUREMENTHANDLER_HPP
#define IGHOUSE_MEASUREMENTHANDLER_HPP

#include <memory>
#include "../sensor/SensorRepository.hpp"

namespace IGHouse
{
namespace Handlers
{

class MeasurementHandler
{
public:
    MeasurementHandler(const std::shared_ptr<SensorRepository> &sensorRepo);

    void runMeasurements();
private:
    std::shared_ptr<SensorRepository> sensorRepo;
};

}//namespace Handlers
}//namespace IGHouse

#endif //IGHOUSE_MEASUREMENTHANDLER_HPP
