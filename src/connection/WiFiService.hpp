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

private:
    String ssid;
    String password;

    void getPreferences();
    bool scanWiFi();
};

}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_WIFISERVICE_HPP
