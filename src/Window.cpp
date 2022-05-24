#include "utils\ErrorSystem.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "singletons\Settings.h"
#include "Window.h"

Window::Window(int InWidth, int InHeight, const std::string& InTitle, GLFWwindow* InWindow)
: Width(InWidth), Height(InHeight), Title(InTitle), DeltaTime(0.f), RawWindow(InWindow)
{
}

Window* Window::NewWindow(int InWidth, int InHeight, const std::string& InTitle)
{
    if (!glfwInit()) THROW_EXCEPTION(INIT_ERROR)

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    GLFWwindow* Win = glfwCreateWindow(InWidth, InHeight, InTitle.c_str(), NULL, NULL);
    if (!Win) THROW_EXCEPTION(CREATE_WIN_ERROR)

    glfwMakeContextCurrent(Win);
    if (!gladLoadGL()) THROW_EXCEPTION(GLAD_ERROR)    

    return new Window(InWidth, InHeight, InTitle.c_str(), Win);    
}

Window* Window::NewWindow()
{
    if (!glfwInit()) THROW_EXCEPTION(INIT_ERROR)

    const WindowData& Data = Settings::Get().WinData;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Data.VersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Data.VersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, Data.Profile);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, Data.Debug);

    GLFWwindow* Win = glfwCreateWindow(Data.Width, Data.Height, Data.Title, NULL, NULL);
    if (!Win) THROW_EXCEPTION(CREATE_WIN_ERROR)

    glfwMakeContextCurrent(Win);
    if (!gladLoadGL()) THROW_EXCEPTION(GLAD_ERROR)

    return new Window(Data.Width, Data.Height, Data.Title, Win);
}

bool Window::IsOpen()
{
    return !glfwWindowShouldClose(RawWindow);
}

void Window::SetTitle(const std::string& InTitle)
{
    glfwSetWindowTitle(RawWindow, InTitle.c_str());
}

float Window::GetDeltaTime()
{
    return DeltaTime;
}

void Window::Update()
{
    static float LastTime = 0.f;
    float CurrentTime = glfwGetTime();
    DeltaTime = CurrentTime - LastTime;
    LastTime = CurrentTime;

    glfwSwapBuffers(RawWindow);
    glfwPollEvents();
}

Window::~Window()
{
    glfwDestroyWindow(RawWindow);
    glfwTerminate();
}