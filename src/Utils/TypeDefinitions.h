#ifndef IGHOUSE_TYPEDEFINITIONS_H
#define IGHOUSE_TYPEDEFINITIONS_H

#include <cstdint>

namespace IGHouse
{

enum class MechanismType : std::uint8_t
{
    UNKNOWN = 255,
    IRRIGATION = 0,
    LIGHT = 1,
    WATTER_LEVEL = 2,
    CRITICAL_WATTER_LEVEL = 3,
    SPRINKLER = 4,
};

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

}//namespace IGHouse

#endif //IGHOUSE_TYPEDEFINITIONS_H
