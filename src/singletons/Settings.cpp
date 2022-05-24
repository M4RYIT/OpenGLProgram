#include "singletons\Settings.h"

Settings& Settings::Get()
{
    static Settings* MainSettings = nullptr;

    if (!MainSettings) MainSettings = new Settings();

    return *MainSettings;
}

void Settings::Init()
{
    Settings& MainSettings = Settings::Get();
}