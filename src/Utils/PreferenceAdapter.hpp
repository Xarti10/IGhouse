#ifndef SZKLARNIA_PREFERENCEADAPTER_HPP
#define SZKLARNIA_PREFERENCEADAPTER_HPP
#include <Preferences.h>
#include <mutex>
#include <memory>

namespace IGHouse
{

struct WiFiPreferences
{
    WiFiPreferences();

    String ssid;
    String password;
    bool valid;
};

struct ThresholdsPreferences{
    ThresholdsPreferences();

    float soilMoisture;
    float humidity;
    float light;
};


class PreferencesAdapter
{
public:
    static WiFiPreferences getWiFiPreferences();
    static void setWiFiPreferences(WiFiPreferences &wifiPrefs);
    static void eraseWiFiPreferences();

    static ThresholdsPreferences getThresholdsPreferences();
    static void setThresholdsPreferences(ThresholdsPreferences &thresholdsPrefs);
    static void eraseThresholdsPreferences();

private:
    static std::mutex preferencesGuard;
    static std::unique_ptr<Preferences> preferences;
};

}//namespace IGHouse


#endif //SZKLARNIA_PREFERENCEADAPTER_HPP
