#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "Scene.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "InputManager.h"

class Application {
private:
    GLFWwindow* window;
    Scene* activeScene;
    int width;
    int height;

    void initGLFW();
    void initWindow();
    void initOpenGL();
    

public:
    Application(int width, int height);
    ~Application();
    Scene* getActiveScene() const { return activeScene; }
    void run(Scene& forestScene, Scene& sphereScene);
    void setScene(Scene* scenePtr);
    InputManager inputManager;
};
