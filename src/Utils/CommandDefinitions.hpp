#ifndef SZKLARNIA_COMMANDDEFINITIONS_HPP
#define SZKLARNIA_COMMANDDEFINITIONS_HPP

namespace IGHouse
{

enum class Command : char
{
    ERASE = 0,
    CONNECT_TO_WIFI,
    RESET,
    GET_SENSOR_DATA,
    UNKNOWN
};

}//namespace IGHouse

#endif //SZKLARNIA_COMMANDDEFINITIONS_HPP
