#ifndef SZKLARNIA_COMMANDDEFINITIONS_HPP
#define SZKLARNIA_COMMANDDEFINITIONS_HPP

namespace IGHouse
{

enum class WiFiCommand : char
{
    ERASE = 0,
    CONNECT_TO_WIFI,
    RESET,
    UNKNOWN
};

enum class ThresholdsDefinition : char
{
    ERASE = 0,
    SET_NEW_THRESHOLDS,
    RESET,
    UNKNOWN
};

}//namespace IGHouse

#endif //SZKLARNIA_COMMANDDEFINITIONS_HPP
