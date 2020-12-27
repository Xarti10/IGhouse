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
    WiFiService(TaskHandle_t &taskHandle);

    void connectWiFi();
    bool getNewPreferences();
    bool scanWiFi();

private:
    String ssid;
    String password;
    static TaskHandle_t connectionTaskHandler;

    static void gotIP(system_event_id_t event);
    static void lostCon(system_event_id_t event);
};

}//namespace Connection
}//namespace IGHouse

#endif //SZKLARNIA_WIFISERVICE_HPP
