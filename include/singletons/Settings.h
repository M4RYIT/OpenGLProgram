#pragma once

struct WindowData
{
    int Width = 800;
    int Height = 600;
    const char* Title = "MainWindow";
    int VersionMajor = 4;
    int VersionMinor = 5;
    int Profile = 0x00032001;
    bool Debug = true;
};

class Settings
{
public:

    WindowData WinData;

    static Settings& Get();

    static void Init();
};