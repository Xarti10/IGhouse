#ifndef IGHOUSE_PINDEFINITIONS_HPP
#define IGHOUSE_PINDEFINITIONS_HPP

#include <cstdint>

namespace IGHouse
{

constexpr std::uint8_t lightMechanismPin = 33;
constexpr std::uint8_t irrigationMechanismPin = 32;
constexpr std::uint8_t sprinklerMechanismPin = 25;
constexpr std::uint8_t waterLeverIndicatorPin = 26;
constexpr std::uint8_t soilMoistureSensorPin = 34;
constexpr std::uint8_t waterLeverSensorPin = 35;


static constexpr float humidityLevelBound = 50.0;
static constexpr float soilMoistureLevelBound = 30.0;
static constexpr float lightLevelBound = 30.0;
}

#endif //IGHOUSE_PINDEFINITIONS_HPP
