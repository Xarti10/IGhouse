#include "PreferenceAdapter.hpp"
#include <Utils/PinDefinitions.hpp>
#include <nvs_flash.h>

namespace IGHouse
{

std::mutex PreferencesAdapter::preferencesGuard;
std::unique_ptr<Preferences> PreferencesAdapter::preferences(new Preferences());

WiFiPreferences::WiFiPreferences()
        : ssid(0.0), password(0.0), valid(false)
{}

ThresholdsPreferences::ThresholdsPreferences()
        : soilMoisture(0.0), humidity(0.0), light(0.0)
{}

WiFiPreferences PreferencesAdapter::getWiFiPreferences()
{
    preferencesGuard.lock();
    WiFiPreferences wifiPrefs;
    preferences->begin("WiFiCred", false);
    wifiPrefs.ssid = preferences->getString("ssid", "");
    wifiPrefs.password = preferences->getString("password", "");
    wifiPrefs.valid = preferences->getBool("valid", false);
    preferences->end();
    preferencesGuard.unlock();
    return wifiPrefs;
}

void PreferencesAdapter::setWiFiPreferences(WiFiPreferences &wifiPrefs)
{
    preferencesGuard.lock();
    preferences->begin("WiFiCred", false);
    preferences->putString("ssid", wifiPrefs.ssid);
    preferences->putString("password", wifiPrefs.password);
    preferences->putBool("valid", wifiPrefs.valid);
    preferences->end();
    preferencesGuard.unlock();
}

void PreferencesAdapter::eraseWiFiPreferences()
{
    preferencesGuard.lock();
    preferences->begin("WiFiCred", false);
    preferences->clear();
    preferences->end();
    preferencesGuard.unlock();
}

ThresholdsPreferences PreferencesAdapter::getThresholdsPreferences()
{
    preferencesGuard.lock();
    ThresholdsPreferences thresholdsPrefs;
    preferences->begin("Thresholds", false);
    thresholdsPrefs.soilMoisture = preferences->getFloat("soilMoisture", defaultSoilMoistureLevelThreshold);
    thresholdsPrefs.humidity = preferences->getFloat("humidity", defaultHumidityLevelThreshold);
    thresholdsPrefs.light = preferences->getFloat("light", defaultLightLevelThreshold);
    preferences->end();
    preferencesGuard.unlock();
    return thresholdsPrefs;
}

void PreferencesAdapter::setThresholdsPreferences(ThresholdsPreferences &thresholdsPrefs)
{
    preferencesGuard.lock();
    preferences->begin("Thresholds", false);
    preferences->putFloat("soilMoisture", thresholdsPrefs.soilMoisture);
    preferences->putFloat("humidity", thresholdsPrefs.humidity);
    preferences->putFloat("light", thresholdsPrefs.light);
    preferences->end();
    preferencesGuard.unlock();
}

void PreferencesAdapter::eraseThresholdsPreferences()
{
    preferencesGuard.lock();
    preferences->begin("Thresholds", false);
    preferences->clear();
    preferences->end();
    preferencesGuard.unlock();
}

}//namespace IGHouse