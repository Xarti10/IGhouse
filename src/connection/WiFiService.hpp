#ifndef SZKLARNIA_WIFISERVICE_HPP
#define SZKLARNIA_WIFISERVICE_HPP

#include <Arduino.h>
#include <WiFi.h>

namespace IGHouse
{
namespace Connection
{


class WiFiService
{
public:
    void connectWiFi();
    void getNewPreferences();
    bool scanWiFi();

private:
    String ssid;
    String password;
};

}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_WIFISERVICE_HPP
