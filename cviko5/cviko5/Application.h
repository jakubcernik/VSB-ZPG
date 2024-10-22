#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "Scene.h"
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "InputManager.h"

class Application {
private:
    GLFWwindow* window;
    Scene* scene;
    int width;
    int height;

    void initGLFW();
    void initWindow();
    void initOpenGL();
    

public:
    Application(int width, int height);
    ~Application();
    void run();
    void setScene(Scene* scenePtr);
    Camera camera;
    InputManager inputManager;
};
