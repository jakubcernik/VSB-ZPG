#pragma once
#include "Scene.h"
#include <GLFW/glfw3.h>

class Application {
private:
    GLFWwindow* window;
    Scene scene;
    int width;
    int height;

    void initGLFW();
    void initWindow();
    void initOpenGL(); // Načítání a nastavení OpenGL kontextu

public:
    Application(int width, int height);
    ~Application();
    void run(); // Spustí hlavní smyčku aplikace
};
