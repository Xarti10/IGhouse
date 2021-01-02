#ifndef IGHOUSE_TYPEDEFINITIONS_HPP
#define IGHOUSE_TYPEDEFINITIONS_HPP

#include <cstdint>
#include <vector>

namespace IGHouse
{

enum class MechanismType : std::uint8_t
{
    UNKNOWN = 255,
    IRRIGATION = 0,
    LIGHT = 1,
    WATER_LEVEL = 2,
    CRITICAL_WATTER_LEVEL = 3,
    SPRINKLER = 4,
};

static const std::vector<MechanismType> mechanismList = {MechanismType::IRRIGATION,
                                                         MechanismType::LIGHT,
                                                         MechanismType::WATER_LEVEL,
                                                         MechanismType::SPRINKLER};

enum class MeasurementType : std::uint8_t
{
    UNKNOWN = 255,
    HUMIDIDY = 0,
    TEMPERATURE = 1,
    LIGHT = 2,
    WATER_LEVEL = 3,
    SOIL_MOISTURE = 4,
    CRITICAL_WATTER_LEVEL = 5,
};

static const std::vector<MeasurementType> measurementList = {MeasurementType::HUMIDIDY,
                                                             MeasurementType::TEMPERATURE,
                                                             MeasurementType::LIGHT,
                                                             MeasurementType::WATER_LEVEL,
                                                             MeasurementType::SOIL_MOISTURE};

}//namespace IGHouse

#endif //IGHOUSE_TYPEDEFINITIONS_HPP
