#pragma once

#include <string>

typedef struct GLFWwindow GLFWwindow;

class Window
{
private:
    int Width;
    int Height;
    std::string Title;
    GLFWwindow* RawWindow;
    float DeltaTime;

    Window(int InWidth, int InHeight, const std::string& InTitle, GLFWwindow* InWindow);
public:
    
    ~Window();
    static Window* NewWindow(int InWidth, int InHeight, const std::string& InTitle);
    static Window* NewWindow();

    bool IsOpen();
    void Update();
    void SetTitle(const std::string& InTitle);
    float GetDeltaTime();
};